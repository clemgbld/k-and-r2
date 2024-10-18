#include "../ex-3-3.c"
#include "../../munit/munit.h"

static MunitResult should_expand_empty_string(const MunitParameter params[],
                                              void *fixture) {
  char s1[] = "";
  char s2[5];
  expand(s1, s2);
  munit_assert_string_equal(s2, "");
  return MUNIT_OK;
}

static MunitResult should_expand_basic_notations(const MunitParameter params[],
                                                 void *fixture) {
  char s1[] = "a-b";
  char s2[100];
  expand(s1, s2);
  munit_assert_string_equal(s2, "ab");

  char s3[] = "a-z";
  char s4[100];
  expand(s3, s4);
  munit_assert_string_equal(s4, "abcdefghijklmnopqrstuvwxyz");

  char s5[] = "A-Z";
  char s6[100];
  expand(s5, s6);
  munit_assert_string_equal(s6, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

  char s7[] = "0-9";
  char s8[100];
  expand(s7, s8);
  munit_assert_string_equal(s8, "0123456789");
  return MUNIT_OK;
}

static MunitResult
should_expand_multiple_basic_notations(const MunitParameter params[],
                                       void *fixture) {
  char s1[] = "a-bA-B";
  char s2[100];
  expand(s1, s2);
  munit_assert_string_equal(s2, "abAB");
  return MUNIT_OK;
}

static MunitResult should_take_leading_literaly(const MunitParameter params[],
                                                void *fixture) {
  char s1[] = "--a-bA-B0-1";
  char s2[100];
  expand(s1, s2);
  munit_assert_string_equal(s2, "--abAB01");
  return MUNIT_OK;
}

static MunitResult
should_handle_wrong_range_separator(const MunitParameter params[],
                                    void *fixture) {
  char s1[] = "a_b0-2";
  char s2[100];
  expand(s1, s2);
  munit_assert_string_equal(s2, "a_b012");
  return MUNIT_OK;
}

static MunitResult
should_have_the_correct_sperator_to_expand(const MunitParameter params[],
                                           void *fixture) {
  char s1[] = "120-3";
  char s2[100];
  expand(s1, s2);
  munit_assert_string_equal(s2, "120123");

  char s3[] = "1--_-2";
  char s4[100];
  expand(s3, s4);
  munit_assert_string_equal(s4, "1--_-2");

  char s5[] = "10-2";
  char s6[100];
  expand(s5, s6);
  munit_assert_string_equal(s6, "1012");
  return MUNIT_OK;
}

MunitTest tests[] = {
    {
        "should expand empty string", /* name */
        should_expand_empty_string,   /* test */
        NULL,                         /* setup */
        NULL,                         /* tear_down */
        MUNIT_TEST_OPTION_NONE,       /* options */
        NULL                          /* parameters */
    },
    {
        "should expand basic notations", /* name */
        should_expand_basic_notations,   /* test */
        NULL,                            /* setup */
        NULL,                            /* tear_down */
        MUNIT_TEST_OPTION_NONE,          /* options */
        NULL                             /* parameters */
    },
    {
        "should expand multiple basic notations", /* name */
        should_expand_multiple_basic_notations,   /* test */
        NULL,                                     /* setup */
        NULL,                                     /* tear_down */
        MUNIT_TEST_OPTION_NONE,                   /* options */
        NULL                                      /* parameters */
    },
    {
        "should take leading literally", /* name */
        should_take_leading_literaly,    /* test */
        NULL,                            /* setup */
        NULL,                            /* tear_down */
        MUNIT_TEST_OPTION_NONE,          /* options */
        NULL                             /* parameters */
    },
    {
        "should handle wrong range separator", /* name */
        should_handle_wrong_range_separator,   /* test */
        NULL,                                  /* setup */
        NULL,                                  /* tear_down */
        MUNIT_TEST_OPTION_NONE,                /* options */
        NULL                                   /* parameters */
    },
    {
        "should have the correct separator to expand", /* name */
        should_have_the_correct_sperator_to_expand,    /* test */
        NULL,                                          /* setup */
        NULL,                                          /* tear_down */
        MUNIT_TEST_OPTION_NONE,                        /* options */
        NULL                                           /* parameters */
    },
    /* Mark the end of the array with an entry where the test
     * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/expand-suite ",       /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
