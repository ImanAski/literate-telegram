#include "defs.h"
#include "funcs.h"
#include "structs.h"
#include "enums.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global State
static Command commands[MAX_COMMANDS];
static size_t command_count = 0;
static Function functions[MAX_FUNCTIONS];
static size_t function_count = 0;
static double variables[26];
static Token tokens[MAX_TOKENS];
static size_t token_count = 0;
static size_t token_pos = 0;
static Token math_tokens[MAX_TOKENS];
static size_t math_token_count = 0;
static size_t math_token_pos = 0;

void print_usage(void) {
  printf("\t-v for version\n\t-h for help\n\t-r for REPL\n");
}
void print_version(void) {
  printf("Program %s by Sohpos %s\n", APP_NAME, APP_VERSION);
}

int main(int argc, char **argv) {

  if (argc == 2) {
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
      print_usage();
      exit(1);
    } else if (strcmp(argv[1], "-v") == 0 ||
               strcmp(argv[1], "--version") == 0) {
      print_version();
      exit(1);
    } else if (strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "--repl") == 0) {
      init_repl();
      exit(0);
    }
  }

  tokenize("let f := 5", tokens, &token_count, MAX_TOKENS);

  printf("%p\n", tokens);

  Point *pt = make_point(4, 5);
  printf("%s\n", point_to_string(*pt));

  Point *pt2 = make_point(6, 7);
  printf("%s\n", point_to_string(*pt2));

  Line *ln = make_line(*pt, *pt2);
  printf("%s\n", line_to_string(*ln));

  Circle *cr = make_circle(*pt, 10);
  printf("%s\n", circle_to_string(*cr));

  return 0;
}
