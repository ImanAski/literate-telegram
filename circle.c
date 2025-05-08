#include "funcs.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

Circle *make_circle(Point c, int r) {
  Circle *cr = (Circle *)malloc(sizeof(Circle));

  cr->c = c;
  cr->r = r;

  return cr;
}

char *circle_to_string(Circle cr) {
  char *r = (char *)malloc(160 * sizeof(char));

  if (r == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  sprintf(r, "{Circle}: center -> %s , radius -> %d", point_to_string(cr.c),
          cr.r);

  return r;
}
