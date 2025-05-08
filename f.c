#include "termios.h"
#include "unistd.h"
#include <ctype.h>
#include <setjmp.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 100
#define MAX_LINES 100
#define MAX_INPUT 1024

struct termios orig_termios;

void disable_raw_mode(void);

void enable_raw_mode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disable_raw_mode);

  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON);
  raw.c_cc[VMIN] = 1;
  raw.c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); }

void clear_screen() {
  write(STDOUT_FILENO, "\033[2J\033[H", 7); // ANSI: clear screen + home }
}

void move_cursor(int row) {
  printf("\033[%d;1H", row + 2); // move to row (offset by 2 lines for header)
}

void print_all_lines(char *lines[], int line_count, int current) {
  for (int i = 0; i < line_count; i++) {
    move_cursor(i);
    printf("\033[K"); // clear line
    if (i == current) {
      printf("> %s", lines[i]);
    } else {
      printf("  %s", lines[i]);
    }
  }
  fflush(stdout);
}

char *readline() {
  size_t size = 128;
  size_t len = 0;
  char *buf = malloc(size);

  if (buf == NULL)
    return NULL;

  int c;
  while ((c = getchar()) != EOF && c != '\n') {
    if (len + 1 >= size) {
      size *= 2;
      char *newbuf = realloc(buf, size);
      if (!newbuf) {
        free(buf);
        return NULL;
      }
      buf = newbuf;
    }
    buf[len++] = c;
  }
  buf[len] = '\0';
  return buf;
}

void writebuffer(char *text, char *buf[], int line) {
  printf("Writing to output\n");

  buf[line] = strdup(text);
  if (buf[line] == NULL) {
    fprintf(stderr, "Failed to allocate memory");
    exit(1);
  }
  sprintf(buf[line], "%s", text);

  printf("Writing completed\n");
}

int main() {
  struct termios original;
  char input[MAX_INPUT] = {0};
  int pos = 0;

  enable_raw_mode();
  clear_screen();
  printf("Editing line (ESC to finish, <CR> for new line):\n> ");
  char *lines[MAX_LINES] = {0};
  int line_count = 5;
  for (int i = 0; i < line_count; i++) {
    lines[i] = calloc(MAX_INPUT, 1);
  }

  int curln = 0;
  int curcs = 0;
  move_cursor(curln);
  // fflush(stdout);

  while (1) {
    char c;
    if (read(STDIN_FILENO, &c, 1) != 1)
      break;

    if (c == 27) {
      char seq[2];
      if (read(STDIN_FILENO, &seq[0], 1) != 1)
        break;
      if (read(STDIN_FILENO, &seq[1], 1) != 1)
        break;

      if (seq[0] == '[') {
        if (seq[1] == 'A') {
          if (curln > 0)
            curln--;
        } else if (seq[1] == 'B') {
          if (curln < line_count - 1)
            curln++;
        }
      }
    } else if (c == '\n') {
      if (curln < line_count - 1)
        curln++;
      curcs = strlen(lines[curln]);
    } else if (c == 127 || c == 8) {
      if (curcs > 0) {
        curcs--;
        lines[curln][curcs] = '\0';
      }
    } else if (isprint(c)) {
      int len = strlen(lines[curln]);
      if (pos < MAX_INPUT - 1) {
        lines[curln][curcs++] = c;
        lines[curln][curcs] = '\0';
        // input[pos++] = c;
        // input[pos] = '\0';
      }
    }

    print_all_lines(lines, line_count, curln);
    // printf("\033[2K\r> %s", input); // Clear line and reprint
    move_cursor(curln);
  }

  disable_raw_mode();

  for (int i = 0; i < line_count; i++) {
    printf("Line %d: %s\n", i + 1, lines[i]);
    free(lines[i]);
  }

  return 0;
  // printf("\nFinal input: %s\n", input);
  // return 0;
  // char **rootbuf = malloc(MAXLINE * sizeof(char *));
  // if (rootbuf == NULL) {
  //   printf("Something is wrong");
  //   return 1;
  // }
  //
  // for (curln = 0; curln < MAXLINE; curln++) {
  //   printf("%d > ", curln);
  //   char *line = readline();
  //   if (!line || line[0] == '\0') {
  //     free(line);
  //     break;
  //   }
  //
  //   writebuffer(line, rootbuf, curln);
  //   free(line);
  // }
  //
  // for (int i = 0; i < MAXLINE; i++) {
  //   if (rootbuf[i] == NULL) {
  //     continue;
  //   }
  //   printf("%d: %s\n", i, rootbuf[i]);
  //   free(rootbuf[i]);
  // }
  //
  // free(rootbuf);
  // return 0;
}
