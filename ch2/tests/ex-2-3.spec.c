
#include "../ex-2-3.c"
#include "../../munit/munit.h"

static MunitResult htoiTest(const MunitParameter params[], void *fixture) {
  munit_assert_int(htoi(""), ==, 0);
  munit_assert_int(htoi("1"), ==, 1);
  munit_assert_int(htoi("5"), ==, 5);
  munit_assert_int(htoi("a"), ==, 10);
  munit_assert_int(htoi("b"), ==, 11);
  munit_assert_int(htoi("c"), ==, 12);
  munit_assert_int(htoi("d"), ==, 13);
  munit_assert_int(htoi("e"), ==, 14);
  munit_assert_int(htoi("f"), ==, 15);
  munit_assert_int(htoi("A"), ==, 10);
  munit_assert_int(htoi("B"), ==, 11);
  munit_assert_int(htoi("C"), ==, 12);
  munit_assert_int(htoi("D"), ==, 13);
  munit_assert_int(htoi("E"), ==, 14);
  munit_assert_int(htoi("F"), ==, 15);
  munit_assert_int(htoi("0x4"), ==, 4);
  munit_assert_int(htoi("0X6"), ==, 6);
  munit_assert_int(htoi("0X6"), ==, 6);
  munit_assert_int(htoi("A2"), ==, 162);
  munit_assert_int(htoi("fF3"), ==, 4083);
  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/htoi-tests ",         /* name */
                         htoiTest,               /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/htoi-tests",          /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
