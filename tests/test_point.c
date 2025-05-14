#include "../defs.h"
#include "../enums.h"
#include "../funcs.h"
#include "../structs.h"
#include "../unity/src/unity.h"
#include "../unity/src/unity_internals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setUp(void) {}
void tearDown(void) {}

void test_makePoint(void) {
  int x = 5;
  int y = 8;

  Point *p = make_point(x, y);
  TEST_ASSERT_EQUAL(p->x, x);
  TEST_ASSERT_EQUAL(p->y, y);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_makePoint);

  return UNITY_END();
}
