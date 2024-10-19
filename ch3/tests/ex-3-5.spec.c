
#include "../ex-3-5.c"
#include "../../munit/munit.h"

static MunitResult common_base_tests(const MunitParameter params[],
                                     void *fixture) {
  char s1[100] = "";
  itob(150, s1, 10);
  munit_assert_string_equal(s1, "150");

  char s2[100] = "";
  itob(-102, s2, 10);
  munit_assert_string_equal(s2, "-102");

  char s3[100] = "";
  itob(-2147483648, s3, 10);
  munit_assert_string_equal(s3, "-2147483648");

  char s4[100] = "";
  itob(229, s4, 8);
  munit_assert_string_equal(s4, "345");
  return MUNIT_OK;
}

static MunitResult base_1_tests(const MunitParameter params[], void *fixture) {
  char s1[100] = "";
  itob(0, s1, 1);
  munit_assert_string_equal(s1, "");

  char s2[100] = "";
  itob(1, s2, 1);
  munit_assert_string_equal(s2, "1");

  char s3[100] = "";
  itob(5, s3, 1);
  munit_assert_string_equal(s3, "11111");
  return MUNIT_OK;
}

static MunitResult base_16_tests(const MunitParameter params[], void *fixture) {
  char s1[100] = "";
  itob(10, s1, 16);
  munit_assert_string_equal(s1, "A");

  char s2[100] = "";
  itob(11, s2, 16);
  munit_assert_string_equal(s2, "B");

  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "common base tests ",   /* name */
                         common_base_tests,      /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     {
                         "base 1 tests ",        /* name */
                         base_1_tests,           /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     {
                         "base 16 tests ",       /* name */
                         base_16_tests,          /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/itob-suite ",         /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
