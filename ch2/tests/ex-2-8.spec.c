#include "../ex-2-8.c"
#include "../../munit/munit.h"
#include <stdint.h>

static MunitResult rightrotTest(const MunitParameter params[], void *fixture) {
  munit_assert_int(rightrot(22, 2), ==, 2147483653UL);

  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/rightrot-tests ",     /* name */
                         rightrotTest,           /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/rightrot-tests",      /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
