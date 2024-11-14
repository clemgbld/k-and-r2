#include "./lowercase.h"
#include "../../munit/munit.h"
#include <stdlib.h>

static MunitResult strcat_test(const MunitParameter params[], void *fixture) {

  char *result1 = lowercase("a");
  munit_assert_string_equal(result1, "a");
  free(result1);

  char *result2 = lowercase("Z");
  munit_assert_string_equal(result2, "z");
  free(result2);

  char *result3 = lowercase("]");
  munit_assert_string_equal(result3, "]");
  free(result3);

  char *result4 = lowercase("A");
  munit_assert_string_equal(result4, "a");
  free(result4);

  char *result5 = lowercase("B");
  munit_assert_string_equal(result5, "b");
  free(result5);

  char *result6 = lowercase("xB");
  munit_assert_string_equal(result6, "xb");
  free(result6);

  char *result7 = lowercase("AbC");
  munit_assert_string_equal(result7, "abc");
  free(result7);

  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/lowercase-test",      /* name */
                         strcat_test,            /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/lower-case-suite ",   /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
