#include "../ex-5-6.c"
#include "../../munit/munit.h"

static MunitResult reverseTest(const MunitParameter params[], void *fixture) {
  char s0[] = "";
  reverse(s0);
  munit_assert_string_equal(s0, "");
  char s1[] = "s";
  reverse(s1);
  munit_assert_string_equal(s1, "s");

  char s2[] = "sw";
  reverse(s2);
  munit_assert_string_equal(s2, "ws");

  char s3[] = "attend oh";
  reverse(s3);
  munit_assert_string_equal(s3, "ho dnetta");

  char s4[100] = "051";
  reverse(s4);
  munit_assert_string_equal(s4, "150");

  return MUNIT_OK;
}

static MunitResult itoa_tests(const MunitParameter params[], void *fixture) {
  char s1[100] = "";
  itoa(150, s1);
  munit_assert_string_equal(s1, "150");

  char s2[100] = "";
  itoa(-102, s2);
  munit_assert_string_equal(s2, "-102");

  char s3[100] = "";
  itoa(-2147483648, s3);
  munit_assert_string_equal(s3, "-2147483648");
  return MUNIT_OK;
}

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

static MunitResult atoi_tests(const MunitParameter params[], void *fixture) {
  munit_assert_int(atoiCustom("0"), ==, 0);
  munit_assert_int(atoiCustom("123"), ==, 123);
  return MUNIT_OK;
}

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

static MunitResult strindex_tests(const MunitParameter params[],
                                  void *fixture) {
  munit_assert_int(strindex("123", "23"), ==, 1);
  munit_assert_int(strindex("143", "23"), ==, -1);
  munit_assert_int(strindex("asterix and obelix", "obelix"), ==, 12);
  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/reverse-test",        /* name */
                         reverseTest,            /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     {
                         "/itoa-tests ",         /* name */
                         itoa_tests,             /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     {
                         "/atof-tests",          /* name */
                         atof_tests,             /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     {
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
                     {
                         "/atoi-tests",          /* name */
                         atoi_tests,             /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     {
                         "/strindex-tests",      /* name */
                         strindex_tests,         /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/test-suite ",         /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
