#include "../flatten-deep.c"
#include "../../munit/munit.h"
#include <stdlib.h>

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

  // 2
  struct wordscount *w3 = NULL;

  flatten_deep(NULL, w3);
  munit_assert_null(w3);

  // 3
  struct wordscount w4[100];
  struct tnode *t2 = talloc();
  t2->word = "the";
  t2->count = 5;
  struct tnode *t3 = talloc();
  t3->word = "c";
  t3->count = 4;
  struct tnode *t4 = talloc();
  t4->word = "programming";
  t4->count = 3;
  t2->left = t4;
  t4->left = t3;

  struct wordscount w5[] = {{"c", 4}, {"programming", 3}, {"the", 5}};

  flatten_deep(t2, w4);

  assert_words_count_equal(w4, w5, 3);
  free(t3);
  free(t4);
  free(t2);

  // 4
  struct wordscount w6[100];
  struct tnode *t5 = talloc();
  t5->word = "the";
  t5->count = 5;
  struct tnode *t6 = talloc();
  t6->word = "c";
  t6->count = 4;
  struct tnode *t7 = talloc();
  t7->word = "programming";
  t7->count = 3;
  t5->left = t7;
  t7->left = t6;
  struct tnode *t8 = talloc();
  t8->word = "zebra";
  t8->count = 6;
  struct tnode *t9 = talloc();
  t9->word = "fast";
  t9->count = 7;
  t5->right = t8;
  t6->right = t9;

  struct wordscount w7[] = {
      {"c", 4}, {"fast", 7}, {"programming", 3}, {"the", 5}, {"zebra", 6}};

  flatten_deep(t5, w6);

  assert_words_count_equal(w6, w7, 5);
  free(t9);
  free(t8);
  free(t7);
  free(t6);
  free(t5);

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
