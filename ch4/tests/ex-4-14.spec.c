#include "../ex-4-14.c"
#include "../../munit/munit.h"

static MunitResult swapTest(const MunitParameter params[], void *fixture) {

  int x = 5;
  int y = 10;

  swap(int, x, y);

  munit_assert_int(x, ==, 10);
  munit_assert_int(y, ==, 5);

  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/swap-test",           /* name */
                         swapTest,               /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/swap-tests ",         /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
