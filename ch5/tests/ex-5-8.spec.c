#include "../ex-5-8.c"
#include "../../munit/munit.h"

/*
A year divisible by 4 (but not by 100 or 400): 2024.
A year not divisible by 100: 2023.
A year divisible by 400: 2000.
Two years for the condition "either not divisible by 100 (but divisible by 4) or
divisible by 400": 2024 (divisible by 4, not by 100) 2000 (divisible by 400)
*/

static MunitResult day_of_year_test(const MunitParameter params[],
                                    void *fixture) {

  munit_assert_int(day_of_year(1950, 1, 14), ==, 14);

  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/day-of-year",         /* name */
                         day_of_year_test,       /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/dates-suite ",        /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
