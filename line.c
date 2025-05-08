#include "funcs.h"
#include "structs.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Line *make_line(Point start, Point end) {
  Line *ln = (Line *)malloc(sizeof(Line));

  ln->start = start;
  ln->end = end;

  ln->length = sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));

  return ln;
}

int line_length(Line ln) {
  return sqrt(pow(ln.end.x - ln.start.x, 2) + pow(ln.end.y - ln.start.y, 2));
}

char *line_to_string(Line ln) {
  char *r = (char *)malloc(150 * sizeof(char));
  sprintf(r, "{Line}: start -> %s end -> %s, length -> %f",
          point_to_string(ln.start), point_to_string(ln.end), ln.length);
  return r;
}
