
#include "../ex-3-6.c"
#include "../../munit/munit.h"

static MunitResult itoa_tests(const MunitParameter params[], void *fixture) {
  char s1[100] = "";
  itoa(150, s1, 0);
  munit_assert_string_equal(s1, "150");

  char s2[100] = "";
  itoa(-102, s2, 0);
  munit_assert_string_equal(s2, "-102");

  char s3[100] = "";
  itoa(-2147483648, s3, 0);
  munit_assert_string_equal(s3, "-2147483648");

  char s4[100] = "";
  itoa(-5, s3, 3);
  munit_assert_string_equal(s3, " -5");

  char s5[100] = "";
  itoa(6, s5, 4);
  munit_assert_string_equal(s5, "   6");

  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/itoa-tests ",         /* name */
                         itoa_tests,             /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/itoa-suite ",         /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
