#include "../take-first.c"
#include "../../munit/munit.h"

static MunitResult take_first_test(const MunitParameter params[],
                                   void *fixture) {

  char str1[] = "";
  char *result1 = take_first(str1, 1);
  munit_assert_string_equal(result1, "");
  free(result1);

  char str2[] = "a";
  char *result2 = take_first(str2, 1);
  munit_assert_string_equal(result2, "a");
  free(result2);

  char str3[] = "ab";
  char *result3 = take_first(str3, 2);
  munit_assert_string_equal(result3, "ab");
  free(result3);

  char str4[] = "abcd";
  char *result4 = take_first(str4, 3);
  munit_assert_string_equal(result4, "abc");
  free(result4);

  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/take-first-test",     /* name */
                         take_first_test,        /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/take-first-suite ",   /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
