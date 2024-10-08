#include "../ex-2-4.c"
#include "../../munit/munit.h"

static MunitResult squeeze_tests(const MunitParameter params[], void *fixture) {
  char str1[] = "abc";
  squeeze(str1, "9");
  munit_assert_string_equal(str1, "abc");
  char str2[] = "abababab";
  squeeze(str2, "a");
  munit_assert_string_equal(str2, "bbbb");
  char str3[] = "ababacbab";
  squeeze(str3, "ab");
  munit_assert_string_equal(str3, "c");
  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/squeeze-tests ",      /* name */
                         squeeze_tests,          /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/squeeze-suite ",      /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
