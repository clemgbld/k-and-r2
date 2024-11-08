#include "../ex-5-9.c"
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

  munit_assert_int(day_of_year(1953, 1, 14), ==, 14);
  munit_assert_int(day_of_year(2000, 2, 29), ==, 60);
  munit_assert_int(day_of_year(2024, 2, 29), ==, 60);
  munit_assert_int(day_of_year(1953, 2, 29), ==, -1);
  munit_assert_int(day_of_year(1953, 2, -5), ==, -1);
  munit_assert_int(day_of_year(1953, 2, 0), ==, -1);
  munit_assert_int(day_of_year(2000, 13, 15), ==, -1);

  return MUNIT_OK;
}

static MunitResult month_day_test(const MunitParameter params[],
                                  void *fixture) {
  int pmonth1;
  int pday1;
  month_day(1953, 14, &pmonth1, &pday1);
  munit_assert_int(pmonth1, ==, 1);
  munit_assert_int(pday1, ==, 14);

  int pmonth2;
  int pday2;
  month_day(2000, 60, &pmonth2, &pday2);
  munit_assert_int(pmonth2, ==, 2);
  munit_assert_int(pday2, ==, 29);

  int pmonth3;
  int pday3;
  month_day(2024, 60, &pmonth3, &pday3);
  munit_assert_int(pmonth3, ==, 2);
  munit_assert_int(pday3, ==, 29);

  int pmonth4;
  int pday4;
  month_day(2024, 366, &pmonth4, &pday4);
  munit_assert_int(pmonth4, ==, 12);
  munit_assert_int(pday4, ==, 31);

  int pmonth5;
  int pday5;
  month_day(1953, 365, &pmonth5, &pday5);
  munit_assert_int(pmonth5, ==, 12);
  munit_assert_int(pday5, ==, 31);

  int pmonth6 = 0;
  int pday6 = 0;
  month_day(2024, 367, &pmonth6, &pday6);
  munit_assert_int(pmonth6, ==, 0);
  munit_assert_int(pday6, ==, 0);

  int pmonth7 = 0;
  int pday7 = 0;
  month_day(1953, 366, &pmonth7, &pday7);
  munit_assert_int(pmonth7, ==, 0);
  munit_assert_int(pday7, ==, 0);

  int pmonth8 = 5;
  int pday8 = 5;
  month_day(1953, 0, &pmonth8, &pday8);
  munit_assert_int(pmonth8, ==, 5);
  munit_assert_int(pday8, ==, 5);

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
                     {
                         "/mont-day",            /* name */
                         month_day_test,         /* test */
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
