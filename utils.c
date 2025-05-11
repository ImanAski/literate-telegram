#include "funcs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void handle_error(const char *msg) {
  printf("Error: %s\n", msg);
}

char *strdnup(const char *s, size_t n) {
  char *p = malloc(n + 1);
  if (!p) {
    handle_error("Memory allocation failed");
    return NULL;
  }
  strncpy(p, s, n);
  p[n] = '\0';
  return p;
}

char *strdup(const char *s) {
  return strdnup(s, strlen(s));
}
