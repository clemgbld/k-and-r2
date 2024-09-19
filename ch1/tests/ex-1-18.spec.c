#include "../ex-1-18.c"
#include "../../munit/munit.h"

static MunitResult padEndTest(const MunitParameter params[], void *fixture) {
  char *result1 = padEnd("");
  munit_assert_string_equal(result1, "");
  free(result1);
  char *result2 = padEnd("a");
  munit_assert_string_equal(padEnd(result2), "a");
  free(result2);
  char *result3 = padEnd("a ");
  munit_assert_string_equal(padEnd(result3), "a");
  free(result3);
  char *result4 = padEnd("ab ");
  munit_assert_string_equal(padEnd(result4), "ab");
  free(result4);
  char *result5 = padEnd("ab   ");
  munit_assert_string_equal(padEnd(result5), "ab");
  free(result5);
  char *result6 = padEnd("abc   ");
  munit_assert_string_equal(padEnd(result6), "abc");
  free(result6);
  char *result7 = padEnd("abc\t\t");
  munit_assert_string_equal(padEnd(result7), "abc");
  free(result7);
  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/my-test",             /* name */
                         padEndTest,             /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/pad-end-tests",       /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
