#include "../ex-4-1.c"
#include "../../munit/munit.h"

static MunitResult strrindex_tests(const MunitParameter params[],
                                   void *fixture) {

  munit_assert_int(strrindex("", "a"), ==, -1);

  munit_assert_int(strrindex("a", "a"), ==, 0);

  munit_assert_int(strrindex("b", "a"), ==, -1);

  munit_assert_int(strrindex("aba", "a"), ==, 2);

  munit_assert_int(strrindex("aba", "ac"), ==, -1);

  munit_assert_int(strrindex("abc", "ac"), ==, -1);

  munit_assert_int(strrindex("should could abc", "ould"), ==, 11);

  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/strrindex-tests",     /* name */
                         strrindex_tests,        /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/strrindex-suite ",    /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
