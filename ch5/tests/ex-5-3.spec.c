#include "../ex-5-3.c"
#include "../../munit/munit.h"

static MunitResult strcat_test(const MunitParameter params[], void *fixture) {
  char s1[100] = "";
  char s2[100] = "b";
  strcat_custom(s1, s2);
  munit_assert_string_equal(s1, "b");

  char s3[100] = "";
  char s4[100] = "ba";
  strcat_custom(s3, s4);
  munit_assert_string_equal(s3, "ba");

  char s5[100] = "";
  char s6[100] = "hello";
  strcat_custom(s5, s6);
  munit_assert_string_equal(s5, "hello");

  char s7[100] = "y";
  char s8[100] = "hello";
  strcat_custom(s7, s8);
  munit_assert_string_equal(s7, "yhello");

  char s9[100] = "hello";
  char s10[100] = " world";
  strcat_custom(s9, s10);
  munit_assert_string_equal(s9, "hello world");

  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/strcat-test",         /* name */
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
    "/strcat-tests ",       /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
