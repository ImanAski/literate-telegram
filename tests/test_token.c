#include "../defs.h"
#include "../enums.h"
#include "../funcs.h"
#include "../structs.h"
#include "../unity/src/unity.h"
#include "../unity/src/unity_internals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setUp(void) {
  // setting up
  token_count = 0;
}
void tearDown(void) {}

void test_TokenizeVarCount(void) {
  token_count = 0;
  tokenize("var foo string;");
  TEST_ASSERT_EQUAL(4, token_count);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_TokenizeVarCount);

  return UNITY_END();
}
