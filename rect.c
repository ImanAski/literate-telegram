#include "funcs.h"
#include "structs.h"

Rectangle *make_rectangle(Point pts[]) {
  Rectangle *rect;
  Point pt1, pt2, pt3, pt4;
  if ((sizeof &pts / sizeof pts[0]) == 2) {
    pt1 = pts[0];
    pt3 = pts[1];
    rect->pt1 = pt1;
    rect->pt3 = pt3;
  }

  return rect;
}
