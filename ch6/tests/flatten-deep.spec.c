#include "../flatten-deep.c"
#include "../../munit/munit.h"

void assert_words_count_equal(struct wordscount words_count1[],
                              struct wordscount words_count2[], int n) {
  for (int i = 0; i < n; i++) {
    munit_assert_string_equal(words_count1[i].word, words_count2[i].word);
    munit_assert_int(words_count1[i].count, ==, words_count2[i].count);
  }
}

static MunitResult flatten_deep_test(const MunitParameter params[],
                                     void *fixture) {
  // 1
  struct tnode *t1 = talloc();
  t1->word = "word";
  t1->count = 5;

  struct wordscount w1[100];

  flatten_deep(t1, w1);

  struct wordscount w2[] = {{"word", 5}};

  assert_words_count_equal(w1, w2, 1);
  free(t1);

  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "/flatten-deep-test",   /* name */
                         flatten_deep_test,      /* test */
                         NULL,                   /* setup */
                         NULL,                   /* tear_down */
                         MUNIT_TEST_OPTION_NONE, /* options */
                         NULL                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/flatten-deep-suite ", /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
