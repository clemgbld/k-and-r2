#include "../ex-5-4.c"
#include "../../munit/munit.h"

static MunitResult strend_test(const MunitParameter params[], void *fixture) {
  munit_assert_int(strend("", ""), ==, 1);
  munit_assert_int(strend("a", "b"), ==, 0);
  munit_assert_int(strend("ab", "b"), ==, 1);
  munit_assert_int(strend("cb", "ab"), ==, 0);
  munit_assert_int(strend("cbc", "abc"), ==, 0);
  munit_assert_int(strend("bc", "abc"), ==, 0);
  munit_assert_int(strend("", "abc"), ==, 0);
  munit_assert_int(strend("hello world", "world"), ==, 1);

  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/strend-test",         /* name */
                         strend_test,            /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/strend-tests ",       /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
