#include "funcs.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

struct Point *make_point(int x, int y) {
  struct Point *pt = (Point *)malloc(sizeof(Point));

  pt->x = x;
  pt->y = y;

  return pt;
}

char *point_to_string(Point pt) {
  char *r = (char *)malloc(50 * sizeof(char));

  if (r == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  sprintf(r, "{Point}: (%d ,%d)", pt.x, pt.y);

  return r;
}
