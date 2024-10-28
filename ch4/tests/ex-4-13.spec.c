#include "../ex-4-13.c"
#include "../../munit/munit.h"

static MunitResult reverseTest(const MunitParameter params[], void *fixture) {
  char s0[] = "";
  reverse(s0);
  munit_assert_string_equal(s0, "");
  char s1[] = "s";
  reverse(s1);
  munit_assert_string_equal(s1, "s");

  char s2[] = "sw";
  reverse(s2);
  munit_assert_string_equal(s2, "ws");

  char s3[] = "attend oh";
  reverse(s3);
  munit_assert_string_equal(s3, "ho dnetta");

  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/reverse-test",        /* name */
                         reverseTest,            /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/reverse-tests ",      /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
