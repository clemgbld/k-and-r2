#include "directorystr.h"
#include "../../munit/munit.h"
#include <stdlib.h>

static MunitResult directorystr_tests(const MunitParameter params[],
                                      void *fixture) {
  char *result1 = directorystr("");
  munit_assert_string_equal(result1, "");
  free(result1);

  char *result2 = directorystr("a");
  munit_assert_string_equal(result2, "a");
  free(result2);

  char *result3 = directorystr("@");
  munit_assert_string_equal(result3, "");
  free(result3);

  char *result4 = directorystr("Z");
  munit_assert_string_equal(result4, "Z");
  free(result4);

  char *result5 = directorystr("1");
  munit_assert_string_equal(result5, "1");
  free(result5);

  char *result6 = directorystr("@1");
  munit_assert_string_equal(result6, "1");
  free(result6);

  char *result7 = directorystr("@1a|");
  munit_assert_string_equal(result7, "1a");
  free(result7);

  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/directorystr-tests",  /* name */
                         directorystr_tests,     /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/directorystr-suite ", /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
