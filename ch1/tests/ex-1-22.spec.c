#include "../ex-1-22.c"
#include "../../munit/munit.h"

static MunitResult findIndexToBreakTest(const MunitParameter params[],
                                        void *fixture) {
  munit_assert_int(findIndexToBreak("hello", 0, 10), ==, -1);
  munit_assert_int(findIndexToBreak("hello world", 0, 6), ==, 5);
  munit_assert_int(findIndexToBreak("hello\tworld", 0, 6), ==, 5);
  munit_assert_int(findIndexToBreak("he llo world", 0, 10), ==, 6);
  munit_assert_int(findIndexToBreak("he llo world", 7, 10), ==, -1);
  munit_assert_int(findIndexToBreak("hello world", 0, 15), ==, -1);
  munit_assert_int(findIndexToBreak("hello world hello world", 12, 12), ==, -1);
  munit_assert_int(findIndexToBreak("helloworldhello world", 0, 10), ==, 15);
  munit_assert_int(findIndexToBreak("helloworldhelloworld", 0, 10), ==, 10);
  munit_assert_int(findIndexToBreak("helloworldhelloworld", 0, 11), ==, 11);
  munit_assert_int(findIndexToBreak("helloworldhelloworld", 10, 11), ==, 21);
  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/my-test",             /* name */
                         findIndexToBreakTest,   /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/find-index-to-break-tests", /* name */
    tests,                        /* tests */
    NULL,                         /* suites */
    1,                            /* iterations */
    MUNIT_SUITE_OPTION_NONE       /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
