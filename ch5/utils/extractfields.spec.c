#include "extractfields.h"
#include "../../munit/munit.h"
#include <stdlib.h>

static MunitResult extractfields_tests(const MunitParameter params[],
                                       void *fixture) {

  char *result1 = extractfields("", 1, 1);
  munit_assert_string_equal(result1, "");
  free(result1);

  char *result2 = extractfields("a", 1, 1);
  munit_assert_string_equal(result2, "a");
  free(result2);

  char *result3 = extractfields("ab", 1, 1);
  munit_assert_string_equal(result3, "ab");
  free(result3);

  char *result4 = extractfields("abc", 1, 1);
  munit_assert_string_equal(result4, "abc");
  free(result4);

  char *result5 = extractfields("abc efg", 2, 1);
  munit_assert_string_equal(result5, "efg");
  free(result5);

  char *result6 = extractfields("abc", 2, 2);
  munit_assert_string_equal(result6, "");
  free(result6);

  char *result7 = extractfields("abc efg hij", 3, 3);
  munit_assert_string_equal(result7, "hij");
  free(result7);

  char *result8 = extractfields("abc efg hij", 1, 1);
  munit_assert_string_equal(result8, "abc");
  free(result8);

  char *result9 = extractfields("abc efg hij", 1, 2);
  munit_assert_string_equal(result9, "abc efg");
  free(result9);

  char *result10 = extractfields("abc efg hij", 1, 10);
  munit_assert_string_equal(result10, "abc efg hij");
  free(result10);

  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/extractfields-tests", /* name */
                         extractfields_tests,    /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/extractfields-suite ", /* name */
    tests,                   /* tests */
    NULL,                    /* suites */
    1,                       /* iterations */
    MUNIT_SUITE_OPTION_NONE  /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
