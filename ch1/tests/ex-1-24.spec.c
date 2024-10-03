#include "../ex-1-24.c"
#include "../../munit/munit.h"

void assert_arrays_int_equal(int array1[], int array2[], int size) {
  for (int i = 0; i < size; i++) {
    munit_assert_int(array1[i], ==, array2[i]);
  }
}

void assert_arrays_char_equal(char array1[], char array2[], int size) {
  for (int i = 0; i < size; i++) {
    munit_assert_int(array1[i], ==, array2[i]);
  }
}

static char *initial_params[] = {"0", "1", NULL};

static MunitParameterEnum test_params[] = {{"initial", initial_params},
                                           {NULL, NULL}};

static MunitResult shouldCountOpenParenthesis(const MunitParameter params[],
                                              void *fixture) {
  int initial = atoi(munit_parameters_get(params, "initial"));
  int syntaxesCount[] = {initial, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  char modes[] = {0, 0, 0, 0};

  countSyntaxes('(', syntaxesCount, modes);

  assert_arrays_int_equal(
      syntaxesCount, (int[]){initial + 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 12);
  assert_arrays_char_equal(modes, (char[]){0, 0, 0, 0}, 4);

  return MUNIT_OK;
}

static MunitResult shouldCountCloseParenthesis(const MunitParameter params[],
                                               void *fixture) {
  int initial = atoi(munit_parameters_get(params, "initial"));
  int syntaxesCount[] = {0, initial, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  char modes[] = {0, 0, 0, 0};

  countSyntaxes(')', syntaxesCount, modes);

  assert_arrays_int_equal(
      syntaxesCount, (int[]){0, initial + 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 12);
  assert_arrays_char_equal(modes, (char[]){0, 0, 0, 0}, 4);

  return MUNIT_OK;
}

static MunitResult shouldCountOpenBraces(const MunitParameter params[],
                                         void *fixture) {
  int initial = atoi(munit_parameters_get(params, "initial"));
  int syntaxesCount[] = {0, 0, initial, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  char modes[] = {0, 0, 0, 0};

  countSyntaxes('{', syntaxesCount, modes);

  assert_arrays_int_equal(
      syntaxesCount, (int[]){0, 0, initial + 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 12);
  assert_arrays_char_equal(modes, (char[]){0, 0, 0, 0}, 4);

  return MUNIT_OK;
}

static MunitResult shouldCountCloseBraces(const MunitParameter params[],
                                          void *fixture) {
  int initial = atoi(munit_parameters_get(params, "initial"));
  int syntaxesCount[] = {0, 0, 0, initial, 0, 0, 0, 0, 0, 0, 0, 0};
  char modes[] = {0, 0, 0, 0};

  countSyntaxes('}', syntaxesCount, modes);

  assert_arrays_int_equal(
      syntaxesCount, (int[]){0, 0, 0, initial + 1, 0, 0, 0, 0, 0, 0, 0, 0}, 12);
  assert_arrays_char_equal(modes, (char[]){0, 0, 0, 0}, 4);

  return MUNIT_OK;
}

static MunitResult shouldCountOpenBracket(const MunitParameter params[],
                                          void *fixture) {
  int initial = atoi(munit_parameters_get(params, "initial"));
  int syntaxesCount[] = {0, 0, 0, 0, initial, 0, 0, 0, 0, 0, 0, 0};
  char modes[] = {0, 0, 0, 0};

  countSyntaxes('[', syntaxesCount, modes);

  assert_arrays_int_equal(
      syntaxesCount, (int[]){0, 0, 0, 0, initial + 1, 0, 0, 0, 0, 0, 0, 0}, 12);
  assert_arrays_char_equal(modes, (char[]){0, 0, 0, 0}, 4);

  return MUNIT_OK;
}

static MunitResult shouldCountCloseBracket(const MunitParameter params[],
                                           void *fixture) {
  int initial = atoi(munit_parameters_get(params, "initial"));
  int syntaxesCount[] = {0, 0, 0, 0, 0, initial, 0, 0, 0, 0, 0, 0};
  char modes[] = {0, 0, 0, 0};

  countSyntaxes(']', syntaxesCount, modes);

  assert_arrays_int_equal(
      syntaxesCount, (int[]){0, 0, 0, 0, 0, initial + 1, 0, 0, 0, 0, 0, 0}, 12);
  assert_arrays_char_equal(modes, (char[]){0, 0, 0, 0}, 4);

  return MUNIT_OK;
}

static MunitResult shouldCountOpenDoubleQuote(const MunitParameter params[],
                                              void *fixture) {
  int initial = atoi(munit_parameters_get(params, "initial"));
  int syntaxesCount[] = {0, 0, 0, 0, 0, 0, initial, 0, 0, 0, 0, 0};
  char modes[] = {0, 0, 0, 0};

  countSyntaxes('"', syntaxesCount, modes);

  assert_arrays_int_equal(
      syntaxesCount, (int[]){0, 0, 0, 0, 0, 0, initial + 1, 0, 0, 0, 0, 0}, 12);
  assert_arrays_char_equal(modes, (char[]){'"', 0, 0, 0}, 4);

  return MUNIT_OK;
}

static MunitResult shouldCountCloseDoubleQuotes(const MunitParameter params[],
                                                void *fixture) {
  int initial = atoi(munit_parameters_get(params, "initial"));
  int syntaxesCount[] = {0, 0, 0, 0, 0, 0, 0, initial, 0, 0, 0, 0};
  char modes[] = {'"', 0, 0, 0};

  countSyntaxes('"', syntaxesCount, modes);

  assert_arrays_int_equal(
      syntaxesCount, (int[]){0, 0, 0, 0, 0, 0, 0, initial + 1, 0, 0, 0, 0}, 12);
  assert_arrays_char_equal(modes, (char[]){0, 0, 0, 0}, 4);

  return MUNIT_OK;
}

static MunitResult shouldCountOpenSingleQuotes(const MunitParameter params[],
                                               void *fixture) {
  int initial = atoi(munit_parameters_get(params, "initial"));
  int syntaxesCount[] = {0, 0, 0, 0, 0, 0, 0, 0, initial, 0, 0, 0};
  char modes[] = {0, 0, 0, 0};

  countSyntaxes('\'', syntaxesCount, modes);

  assert_arrays_int_equal(
      syntaxesCount, (int[]){0, 0, 0, 0, 0, 0, 0, 0, initial + 1, 0, 0, 0}, 12);
  assert_arrays_char_equal(modes, (char[]){'\'', 0, 0, 0}, 4);

  return MUNIT_OK;
}

static MunitResult shouldCountCloseSingleQuotes(const MunitParameter params[],
                                                void *fixture) {
  int initial = atoi(munit_parameters_get(params, "initial"));
  int syntaxesCount[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, initial, 0, 0};
  char modes[] = {'\'', 0, 0, 0};

  countSyntaxes('\'', syntaxesCount, modes);

  assert_arrays_int_equal(
      syntaxesCount, (int[]){0, 0, 0, 0, 0, 0, 0, 0, 0, initial + 1, 0, 0}, 12);
  assert_arrays_char_equal(modes, (char[]){0, 0, 0, 0}, 4);

  return MUNIT_OK;
}

static MunitResult shouldInitializeCommentMode(const MunitParameter params[],
                                               void *fixture) {
  int syntaxesCount[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  char modes[] = {0, 0, 0, 0};

  countSyntaxes('/', syntaxesCount, modes);

  assert_arrays_int_equal(syntaxesCount,
                          (int[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 12);
  assert_arrays_char_equal(modes, (char[]){'/', 0, 0, 0}, 4);

  return MUNIT_OK;
}

static MunitResult shouldCountOpenComments(const MunitParameter params[],
                                           void *fixture) {
  int initial = atoi(munit_parameters_get(params, "initial"));
  int syntaxesCount[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, initial, 0};
  char modes[] = {'/', 0, 0, 0};

  countSyntaxes('*', syntaxesCount, modes);

  assert_arrays_int_equal(
      syntaxesCount, (int[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, initial + 1, 0}, 12);
  assert_arrays_char_equal(modes, (char[]){'/', '*', 0, 0}, 4);

  return MUNIT_OK;
}

static MunitResult shouldInitializeCloseComment(const MunitParameter params[],
                                                void *fixture) {
  int syntaxesCount[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  char modes[] = {'/', '*', 0, 0};

  countSyntaxes('*', syntaxesCount, modes);

  assert_arrays_int_equal(syntaxesCount,
                          (int[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 12);
  assert_arrays_char_equal(modes, (char[]){'/', '*', '*', 0}, 4);

  return MUNIT_OK;
}

static MunitResult shouldCountCloseComments(const MunitParameter params[],
                                            void *fixture) {
  int initial = atoi(munit_parameters_get(params, "initial"));
  int syntaxesCount[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, initial};
  char modes[] = {'/', '*', '*', 0};

  countSyntaxes('/', syntaxesCount, modes);

  assert_arrays_int_equal(
      syntaxesCount, (int[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 00, initial + 1},
      12);
  assert_arrays_char_equal(modes, (char[]){0, 0, 0, 0}, 4);

  return MUNIT_OK;
}

MunitTest tests[] = {{
                         "should count open parenthesis", /* name */
                         shouldCountOpenParenthesis,      /* test */
                         NULL,                            /* setup */
                         NULL,                            /* tear_down */
                         MUNIT_TEST_OPTION_NONE,          /* options */
                         test_params                      /* parameters */
                     },
                     {
                         "should count close parenthesis", /* name */
                         shouldCountCloseParenthesis,      /* test */
                         NULL,                             /* setup */
                         NULL,                             /* tear_down */
                         MUNIT_TEST_OPTION_NONE,           /* options */
                         test_params                       /* parameters */
                     },
                     {
                         "should count open braces", /* name */
                         shouldCountOpenBraces,      /* test */
                         NULL,                       /* setup */
                         NULL,                       /* tear_down */
                         MUNIT_TEST_OPTION_NONE,     /* options */
                         test_params                 /* parameters */
                     },
                     {
                         "should count close braces", /* name */
                         shouldCountCloseBraces,      /* test */
                         NULL,                        /* setup */
                         NULL,                        /* tear_down */
                         MUNIT_TEST_OPTION_NONE,      /* options */
                         test_params                  /* parameters */
                     },
                     {
                         "should count open brackets", /* name */
                         shouldCountOpenBracket,       /* test */
                         NULL,                         /* setup */
                         NULL,                         /* tear_down */
                         MUNIT_TEST_OPTION_NONE,       /* options */
                         test_params                   /* parameters */
                     },
                     {
                         "should count close brackets", /* name */
                         shouldCountCloseBracket,       /* test */
                         NULL,                          /* setup */
                         NULL,                          /* tear_down */
                         MUNIT_TEST_OPTION_NONE,        /* options */
                         test_params                    /* parameters */
                     },
                     {
                         "should count open double quotes", /* name */
                         shouldCountOpenDoubleQuote,        /* test */
                         NULL,                              /* setup */
                         NULL,                              /* tear_down */
                         MUNIT_TEST_OPTION_NONE,            /* options */
                         test_params                        /* parameters */
                     },
                     {
                         "should count close doubles quotes", /* name */
                         shouldCountCloseDoubleQuotes,        /* test */
                         NULL,                                /* setup */
                         NULL,                                /* tear_down */
                         MUNIT_TEST_OPTION_NONE,              /* options */
                         test_params                          /* parameters */
                     },
                     {
                         "should count open single quotes", /* name */
                         shouldCountOpenSingleQuotes,       /* test */
                         NULL,                              /* setup */
                         NULL,                              /* tear_down */
                         MUNIT_TEST_OPTION_NONE,            /* options */
                         test_params                        /* parameters */
                     },
                     {
                         "should count close single quotes", /* name */
                         shouldCountCloseSingleQuotes,       /* test */
                         NULL,                               /* setup */
                         NULL,                               /* tear_down */
                         MUNIT_TEST_OPTION_NONE,             /* options */
                         test_params                         /* parameters */
                     },
                     {
                         "should initialize comment mode", /* name */
                         shouldInitializeCommentMode,      /* test */
                         NULL,                             /* setup */
                         NULL,                             /* tear_down */
                         MUNIT_TEST_OPTION_NONE,           /* options */
                         NULL                              /* parameters */
                     },
                     {
                         "should count open comments", /* name */
                         shouldCountOpenComments,      /* test */
                         NULL,                         /* setup */
                         NULL,                         /* tear_down */
                         MUNIT_TEST_OPTION_NONE,       /* options */
                         test_params                   /* parameters */
                     },
                     {
                         "should initialize close comments", /* name */
                         shouldInitializeCloseComment,       /* test */
                         NULL,                               /* setup */
                         NULL,                               /* tear_down */
                         MUNIT_TEST_OPTION_NONE,             /* options */
                         NULL                                /* parameters */
                     },
                     {
                         "should count close comments", /* name */
                         shouldCountCloseComments,      /* test */
                         NULL,                          /* setup */
                         NULL,                          /* tear_down */
                         MUNIT_TEST_OPTION_NONE,        /* options */
                         test_params                    /* parameters */
                     },
                     /* Mark the end of the array with an entry where the test
                      * function is NULL */
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/count-syntaxes ",     /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
