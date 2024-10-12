#include "../ex-2-9.c"
#include "../../munit/munit.h"
#include <stdint.h>

static MunitResult bitcountTest(const MunitParameter params[], void *fixture) {
  munit_assert_int(bitcount(22), ==, 3);
  munit_assert_int(bitcount(8), ==, 1);
  munit_assert_int(bitcount(10), ==, 2);

  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/bitcount-tests ",     /* name */
                         bitcountTest,           /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/bitcount-tests",      /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
