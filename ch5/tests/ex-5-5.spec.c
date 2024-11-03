#include "../ex-5-5.c"
#include "../../munit/munit.h"

static MunitResult strncat_test(const MunitParameter params[], void *fixture) {
  char s1[100] = "";
  char s2[100] = "b";
  strncat_custom(s1, s2, 1);
  munit_assert_string_equal(s1, "b");

  char s3[100] = "";
  char s4[100] = "ba";
  strncat_custom(s3, s4, 2);
  munit_assert_string_equal(s3, "ba");

  char s5[100] = "";
  char s6[100] = "hello";
  strncat_custom(s5, s6, 5);
  munit_assert_string_equal(s5, "hello");

  char s7[100] = "y";
  char s8[100] = "hello";
  strncat_custom(s7, s8, 5);
  munit_assert_string_equal(s7, "yhello");

  char s9[100] = "hello";
  char s10[100] = " world";
  strncat_custom(s9, s10, 6);
  munit_assert_string_equal(s9, "hello world");

  char s11[100] = "hello";
  char s12[100] = " world, from the c programming language";
  strncat_custom(s11, s12, 6);
  munit_assert_string_equal(s11, "hello world");

  return MUNIT_OK;
}

static MunitResult strncpy_test(const MunitParameter params[], void *fixture) {
  char s1[100];
  char s2[100] = "b";
  strncpy_custom(s1, s2, 1);
  munit_assert_string_equal(s1, "b");

  char s3[100];
  char s4[100] = "ba";
  strncpy_custom(s3, s4, 2);
  munit_assert_string_equal(s3, "ba");

  char s5[100];
  char s6[100] = "ba";
  strncpy_custom(s5, s6, 1);
  munit_assert_string_equal(s5, "b");
  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/strncat-test",        /* name */
                         strncat_test,           /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     {
                         "/strncpy-test",        /* name */
                         strncpy_test,           /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/str-tests ",          /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
