
#include "../ex-1-19.c"
#include "../../munit/munit.h"

static MunitResult reverseTest(const MunitParameter params[], void *fixture) {
  char *result1 = reverse("");
  munit_assert_string_equal(result1, "");
  free(result1);
  char *result2 = reverse("a");
  munit_assert_string_equal(result2, "a");
  free(result2);
  char *result3 = reverse("ab");
  munit_assert_string_equal(result3, "ba");
  free(result3);
  char *result4 = reverse("abc");
  munit_assert_string_equal(result4, "cba");
  free(result4);

  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/my-test",             /* name */
                         reverseTest,            /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/reverse-tests",       /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
