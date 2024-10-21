#include "../ex-4-2.c"
#include "../../munit/munit.h"

static MunitResult atof_tests(const MunitParameter params[], void *fixture) {
  munit_assert_double(atofcustom("15.67"), ==, 15.67);
  munit_assert_double(atofcustom("-16.68"), ==, -16.68);
  munit_assert_double(atofcustom("-16.68"), ==, -16.68);
  munit_assert_double(atofcustom("5.67e3"), ==, 5670.0);
  munit_assert_double(atofcustom("4.32E4"), ==, 43200.0);
  munit_assert_double(atofcustom("1.23e-4"), ==, 0.000123);
  munit_assert_double(atofcustom("1.23e-4"), ==, 0.000123);
  munit_assert_double(atofcustom("1.23e-4"), ==, 0.000123);
  munit_assert_double(atofcustom("5.67e+3"), ==, 5670.0);

  munit_assert_double(atofcustom("5.67e+3"), ==, 5670.0);

  munit_assert_double(atofcustom("1.2e10"), ==, 12000000000.000000);
  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/atof-tests",          /* name */
                         atof_tests,             /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/atof-tests",          /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
