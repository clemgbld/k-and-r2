#include "../ex-4-12.c"
#include "../../munit/munit.h"

static MunitResult itoaTest(const MunitParameter params[], void *fixture) {
  char s1[100];
  itoa(1, s1);
  munit_assert_string_equal(s1, "1");

  char s2[100];
  itoa(5, s2);
  munit_assert_string_equal(s2, "5");

  char s3[100];
  itoa(215, s3);
  munit_assert_string_equal(s3, "215");

  char s4[100];
  itoa(-2, s4);
  munit_assert_string_equal(s4, "-2");

  char s5[100];
  itoa(-2147483648, s5);
  munit_assert_string_equal(s5, "-2147483648");

  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/itoa-test",           /* name */
                         itoaTest,               /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/itoa-tests ",         /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
