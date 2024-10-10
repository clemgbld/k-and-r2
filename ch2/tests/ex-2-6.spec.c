
#include "../ex-2-6.c"
#include "../../munit/munit.h"

static MunitResult setBitsTest(const MunitParameter params[], void *fixture) {
  munit_assert_int(setbits(157, 4, 3, 13), ==, 221);

  munit_assert_int(setbits(133, 3, 3, 7), ==, 189);

  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/setbits-tests ",      /* name */
                         setBitsTest,            /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/setbits-tests",       /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
