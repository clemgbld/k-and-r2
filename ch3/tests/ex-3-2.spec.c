#include "../ex-3-2.c"
#include "../../munit/munit.h"

static MunitResult escape_tests(const MunitParameter params[], void *fixture) {
  char s1[] = "hello";
  char s2[6];
  escape(s1, s2);
  munit_assert_string_equal(s1, s2);
  char s3[] = "hel\nlo";
  char s4[20];
  escape(s3, s4);
  munit_assert_string_equal(s4, "hel\\nlo");

  char s5[] = "hel\tlo";
  char s6[20];
  escape(s5, s6);
  munit_assert_string_equal(s6, "hel\\tlo");
  return MUNIT_OK;
}

static MunitResult escapeReverse_tests(const MunitParameter params[],
                                       void *fixture) {
  char s1[] = "hello";
  char s2[6];
  escapeReverse(s1, s2);
  munit_assert_string_equal(s1, s2);
  char s3[] = "hel\\nlo";
  char s4[20];
  escapeReverse(s3, s4);
  munit_assert_string_equal(s4, "hel\nlo");
  char s5[] = "hel\\tlo";
  char s6[20];
  escapeReverse(s5, s6);
  munit_assert_string_equal(s6, "hel\tlo");
  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/escape-tests ",       /* name */
                         escape_tests,           /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     {
                         "/escape_reverse-tests ", /* name */
                         escapeReverse_tests,      /* test */
                         NULL,                     /* setup */
                         NULL,                     /* tear_down */
                         MUNIT_TEST_OPTION_NONE,   /* options */
                         NULL                      /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/escape-suite ",       /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
