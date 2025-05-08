
#include "defs.h"
#include <stdio.h>
#include <string.h>

void init_repl(void) {
  char input[64];

  printf("%s Program by Sophos %s (type :q or :quit for terminating)\n",
         APP_NAME, APP_VERSION);
  printf("> ");
  while (fgets(input, sizeof(input), stdin)) {
    if (strncmp(input, ":quit", 5) == 0 || strncmp(input, ":q", 2) == 0) {
      printf("Goodbye.\n");
      break;
    }

    if (strncmp(input, ":ping", 5) == 0 || strncmp(input, ":p", 2) == 0) {
      printf("Pong :)\n");
      printf("> ");
      continue;
    }

    printf("yout typed: %s", input);
    printf("> ");
  }
}

void quit_repl(void) {}
