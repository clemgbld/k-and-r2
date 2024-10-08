#include "../ex-2-5.c"
#include "../../munit/munit.h"

static MunitResult any_tests(const MunitParameter params[], void *fixture) {
  munit_assert_int(any("", ""), ==, -1);
  munit_assert_int(any("a", "a"), ==, 0);
  munit_assert_int(any("b", "b"), ==, 0);
  munit_assert_int(any("b", "ab"), ==, 0);
  munit_assert_int(any("ca", "ab"), ==, 1);
  munit_assert_int(any("czn", "abn"), ==, 2);

  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/any-tests ",          /* name */
                         any_tests,              /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/any-suite ",          /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
