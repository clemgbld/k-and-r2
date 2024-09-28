#include "../ex-1-23.c"
#include "../../munit/munit.h"

char expectedLogs[2];

void printCharSpy(const char c) {
  if (expectedLogs[0] == 0) {
    expectedLogs[0] = c;
  } else {
    expectedLogs[1] = c;
  }
}

Logger logger;

static void *before_each(const MunitParameter params[], void *user_data) {

  expectedLogs[0] = 0;
  expectedLogs[1] = 0;

  logger.printChar = printCharSpy;

  return 0;
}

static MunitResult
shouldPassInQuoteModeAndPrintAQuote(const MunitParameter params[],
                                    void *fixture) {

  char comments[4] = {'/', 0, 0, 0};

  removeComments('"', comments, &logger);
  munit_assert_int(expectedLogs[0], ==, '/');
  munit_assert_int(expectedLogs[1], ==, '"');
  munit_assert_int(comments[0], ==, '"');
  munit_assert_int(comments[1], ==, 0);
  munit_assert_int(comments[2], ==, 0);
  munit_assert_int(comments[3], ==, 0);

  return MUNIT_OK;
}

static MunitResult
shouldNotPrintAnythingWhenInMultiCommentsMode(const MunitParameter params[],
                                              void *fixture) {

  char comments[4] = {'/', '*', 0, 0};

  removeComments('i', comments, &logger);
  munit_assert_int(expectedLogs[0], ==, 0);
  munit_assert_int(expectedLogs[1], ==, 0);
  munit_assert_int(comments[0], ==, '/');
  munit_assert_int(comments[1], ==, '*');
  munit_assert_int(comments[2], ==, 0);
  munit_assert_int(comments[3], ==, 0);

  return MUNIT_OK;
}

static MunitResult
shouldNotPrintAnythingWhenEncounteringTheFirstSlashOfAPotentialComment(
    const MunitParameter params[], void *fixture) {

  char comments[4] = {0, 0, 0, 0};

  removeComments('/', comments, &logger);
  munit_assert_int(expectedLogs[0], ==, 0);
  munit_assert_int(expectedLogs[1], ==, 0);
  munit_assert_int(comments[0], ==, '/');
  munit_assert_int(comments[1], ==, 0);
  munit_assert_int(comments[2], ==, 0);
  munit_assert_int(comments[3], ==, 0);

  return MUNIT_OK;
}

static MunitResult
shouldBeAbleToPassInMultiCommentsMode(const MunitParameter params[],
                                      void *fixture) {

  char comments[4] = {'/', 0, 0, 0};

  removeComments('*', comments, &logger);
  munit_assert_int(expectedLogs[0], ==, 0);
  munit_assert_int(expectedLogs[1], ==, 0);
  munit_assert_int(comments[0], ==, '/');
  munit_assert_int(comments[1], ==, '*');
  munit_assert_int(comments[2], ==, 0);
  munit_assert_int(comments[3], ==, 0);

  return MUNIT_OK;
}

static MunitResult shouldPrintTheFirstSlashIfTheNextCharacterIsNotAStar(
    const MunitParameter params[], void *fixture) {

  char comments[4] = {'/', 0, 0, 0};

  removeComments('c', comments, &logger);
  munit_assert_int(expectedLogs[0], ==, '/');
  munit_assert_int(expectedLogs[1], ==, 'c');
  munit_assert_int(comments[0], ==, 0);
  munit_assert_int(comments[1], ==, 0);
  munit_assert_int(comments[2], ==, 0);
  munit_assert_int(comments[3], ==, 0);

  return MUNIT_OK;
}

static MunitResult
shouldBeAbleToPassInLineCommentMode(const MunitParameter params[],
                                    void *fixture) {

  char comments[4] = {'/', 0, 0, 0};

  removeComments('/', comments, &logger);
  munit_assert_int(expectedLogs[0], ==, 0);
  munit_assert_int(expectedLogs[1], ==, 0);
  munit_assert_int(comments[0], ==, '/');
  munit_assert_int(comments[1], ==, '/');
  munit_assert_int(comments[2], ==, 0);
  munit_assert_int(comments[3], ==, 0);

  return MUNIT_OK;
}

static MunitResult
shouldNotPrintAnythingInLineCommentMode(const MunitParameter params[],
                                        void *fixture) {
  char comments[4] = {'/', '/', 0, 0};

  removeComments('c', comments, &logger);
  munit_assert_int(expectedLogs[0], ==, 0);
  munit_assert_int(expectedLogs[1], ==, 0);
  munit_assert_int(comments[0], ==, '/');
  munit_assert_int(comments[1], ==, '/');
  munit_assert_int(comments[2], ==, 0);
  munit_assert_int(comments[3], ==, 0);

  return MUNIT_OK;
}

static MunitResult shouldExitLineCommentModeWhenEncounteringANewLineChar(
    const MunitParameter params[], void *fixture) {
  char comments[4] = {'/', '/', 0, 0};

  removeComments('\n', comments, &logger);
  munit_assert_int(expectedLogs[0], ==, '\n');
  munit_assert_int(expectedLogs[1], ==, 0);
  munit_assert_int(comments[0], ==, 0);
  munit_assert_int(comments[1], ==, 0);
  munit_assert_int(comments[2], ==, 0);
  munit_assert_int(comments[3], ==, 0);

  return MUNIT_OK;
}

static MunitResult
shouldNotExitTheMultiLineModeWhenEncounteringANewLineCharacter(
    const MunitParameter params[], void *fixture) {
  char comments[4] = {'/', '*', 0, 0};

  removeComments('\n', comments, &logger);
  munit_assert_int(expectedLogs[0], ==, 0);
  munit_assert_int(expectedLogs[1], ==, 0);
  munit_assert_int(comments[0], ==, '/');
  munit_assert_int(comments[1], ==, '*');
  munit_assert_int(comments[2], ==, 0);
  munit_assert_int(comments[3], ==, 0);

  return MUNIT_OK;
}

static MunitResult shouldNotSwitchFromMultiLineCommentsModeToLineCommentMode(
    const MunitParameter params[], void *fixture) {
  char comments[4] = {'/', '*', 0, 0};

  removeComments('/', comments, &logger);
  munit_assert_int(expectedLogs[0], ==, 0);
  munit_assert_int(expectedLogs[1], ==, 0);
  munit_assert_int(comments[0], ==, '/');
  munit_assert_int(comments[1], ==, '*');
  munit_assert_int(comments[2], ==, 0);
  munit_assert_int(comments[3], ==, 0);

  return MUNIT_OK;
}

static MunitResult
shouldStartToInitiateTheMultiLineCommentsExit(const MunitParameter params[],
                                              void *fixture) {
  char comments[4] = {'/', '*', 0, 0};

  removeComments('*', comments, &logger);
  munit_assert_int(expectedLogs[0], ==, 0);
  munit_assert_int(expectedLogs[1], ==, 0);
  munit_assert_int(comments[0], ==, '/');
  munit_assert_int(comments[1], ==, '*');
  munit_assert_int(comments[2], ==, '*');
  munit_assert_int(comments[3], ==, 0);

  return MUNIT_OK;
}

static MunitResult
shouldBeAbleToExitTheMultiLineCommentsMode(const MunitParameter params[],
                                           void *fixture) {
  char comments[4] = {'/', '*', '*', 0};

  removeComments('/', comments, &logger);
  munit_assert_int(expectedLogs[0], ==, 0);
  munit_assert_int(expectedLogs[1], ==, 0);
  munit_assert_int(comments[0], ==, 0);
  munit_assert_int(comments[1], ==, 0);
  munit_assert_int(comments[2], ==, 0);
  munit_assert_int(comments[3], ==, 0);

  return MUNIT_OK;
}

static MunitResult
shouldQuitInitiatingTheMultineCommentsExitWhenTheLastCharIsNotASlash(
    const MunitParameter params[], void *fixture) {
  char comments[4] = {'/', '*', '*', 0};

  removeComments('c', comments, &logger);
  munit_assert_int(expectedLogs[0], ==, 0);
  munit_assert_int(expectedLogs[1], ==, 0);
  munit_assert_int(comments[0], ==, '/');
  munit_assert_int(comments[1], ==, '*');
  munit_assert_int(comments[2], ==, 0);
  munit_assert_int(comments[3], ==, 0);

  return MUNIT_OK;
}

static MunitResult
shouldPrintSlashAnywayWhenInQuoteMode(const MunitParameter params[],
                                      void *fixture) {
  char comments[4] = {'"', 0, 0, 0};

  removeComments('/', comments, &logger);
  munit_assert_int(expectedLogs[0], ==, '/');
  munit_assert_int(expectedLogs[1], ==, 0);
  munit_assert_int(comments[0], ==, '"');
  munit_assert_int(comments[1], ==, 0);
  munit_assert_int(comments[2], ==, 0);
  munit_assert_int(comments[3], ==, 0);

  return MUNIT_OK;
}

static MunitResult
shouldPrintStarAnywayWhenInQuoteMode(const MunitParameter params[],
                                     void *fixture) {
  char comments[4] = {'"', 0, 0, 0};

  removeComments('*', comments, &logger);
  munit_assert_int(expectedLogs[0], ==, '*');
  munit_assert_int(expectedLogs[1], ==, 0);
  munit_assert_int(comments[0], ==, '"');
  munit_assert_int(comments[1], ==, 0);
  munit_assert_int(comments[2], ==, 0);
  munit_assert_int(comments[3], ==, 0);

  return MUNIT_OK;
}

static MunitResult
shouldNotPrintQuoteWhenInMultiLineCommentsMode(const MunitParameter params[],
                                               void *fixture) {
  char comments[4] = {'/', '*', 0, 0};

  removeComments('"', comments, &logger);
  munit_assert_int(expectedLogs[0], ==, 0);
  munit_assert_int(expectedLogs[1], ==, 0);
  munit_assert_int(comments[0], ==, '/');
  munit_assert_int(comments[1], ==, '*');
  munit_assert_int(comments[2], ==, 0);
  munit_assert_int(comments[3], ==, 0);

  return MUNIT_OK;
}

static MunitResult
shouldNotPrintQuoteWhenInLineCommentMode(const MunitParameter params[],
                                         void *fixture) {
  char comments[4] = {'/', '/', 0, 0};

  removeComments('"', comments, &logger);
  munit_assert_int(expectedLogs[0], ==, 0);
  munit_assert_int(expectedLogs[1], ==, 0);
  munit_assert_int(comments[0], ==, '/');
  munit_assert_int(comments[1], ==, '/');
  munit_assert_int(comments[2], ==, 0);
  munit_assert_int(comments[3], ==, 0);

  return MUNIT_OK;
}

static MunitResult shouldBeAbleToExitTheQuoteMode(const MunitParameter params[],
                                                  void *fixture) {
  char comments[4] = {'"', 0, 0, 0};

  removeComments('"', comments, &logger);
  munit_assert_int(expectedLogs[0], ==, '"');
  munit_assert_int(expectedLogs[1], ==, 0);
  munit_assert_int(comments[0], ==, 0);
  munit_assert_int(comments[1], ==, 0);
  munit_assert_int(comments[2], ==, 0);
  munit_assert_int(comments[3], ==, 0);

  return MUNIT_OK;
}

static MunitResult
shouldNotModifyTheCommentsStateWhenEncouteringAStartWitoutHavingEncouterASlashBefore(
    const MunitParameter params[], void *fixture) {
  char comments[4] = {0, 0, 0, 0};

  removeComments('*', comments, &logger);
  munit_assert_int(expectedLogs[0], ==, '*');
  munit_assert_int(expectedLogs[1], ==, 0);
  munit_assert_int(comments[0], ==, 0);
  munit_assert_int(comments[1], ==, 0);
  munit_assert_int(comments[2], ==, 0);
  munit_assert_int(comments[3], ==, 0);

  return MUNIT_OK;
}

MunitTest tests[] = {
    {
        "should pass in quote mode and print a quote", /* name */
        shouldPassInQuoteModeAndPrintAQuote,           /* test */
        before_each,                                   /* setup */
        NULL,                                          /* tear_down */
        MUNIT_TEST_OPTION_NONE,                        /* options */
        NULL                                           /* parameters */
    },
    {
        "should not print anything in multi comment mode", /* name */
        shouldNotPrintAnythingWhenInMultiCommentsMode,     /* test */
        before_each,                                       /* setup */
        NULL,                                              /* tear_down */
        MUNIT_TEST_OPTION_NONE,                            /* options */
        NULL                                               /* parameters */
    },
    {
        "should not print anything when encountering the first slash of a "
        "comment "
        "potential comment", /* name */
        shouldNotPrintAnythingWhenEncounteringTheFirstSlashOfAPotentialComment, /* test */
        before_each,            /* setup */
        NULL,                   /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "should be able to pass in multi comments mode", /* name */
        shouldBeAbleToPassInMultiCommentsMode,           /* test */
        before_each,                                     /* setup */
        NULL,                                            /* tear_down */
        MUNIT_TEST_OPTION_NONE,                          /* options */
        NULL                                             /* parameters */
    },
    {
        "should print the first slash if the next character is not a star", /* name
                                                                             */
        shouldPrintTheFirstSlashIfTheNextCharacterIsNotAStar, /* test */
        before_each,                                          /* setup */
        NULL,                                                 /* tear_down */
        MUNIT_TEST_OPTION_NONE,                               /* options */
        NULL                                                  /* parameters */
    },
    {
        "should be able to pass in line comment mode", /* name
                                                        */
        shouldBeAbleToPassInLineCommentMode,           /* test */
        before_each,                                   /* setup */
        NULL,                                          /* tear_down */
        MUNIT_TEST_OPTION_NONE,                        /* options */
        NULL                                           /* parameters */
    },
    {
        "should not print anything in line comment mode", /* name
                                                           */
        shouldNotPrintAnythingInLineCommentMode,          /* test */
        before_each,                                      /* setup */
        NULL,                                             /* tear_down */
        MUNIT_TEST_OPTION_NONE,                           /* options */
        NULL                                              /* parameters */
    },
    {
        "should exit the line comment mode when encountering a new line "
        "char",                                                /* name
                                                                */
        shouldExitLineCommentModeWhenEncounteringANewLineChar, /* test */
        before_each,                                           /* setup */
        NULL,                                                  /* tear_down */
        MUNIT_TEST_OPTION_NONE,                                /* options */
        NULL                                                   /* parameters */
    },
    {
        "shouldn't exit the multi line mode when encountering a new line "
        "char",                                                         /* name
                                                                         */
        shouldNotExitTheMultiLineModeWhenEncounteringANewLineCharacter, /* test
                                                                         */
        before_each,            /* setup */
        NULL,                   /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },

    {
        "should not switch from multi line comments to line comment mode", /* name
                                                                            */
        shouldNotSwitchFromMultiLineCommentsModeToLineCommentMode, /* test
                                                                    */
        before_each,                                               /* setup */
        NULL,                   /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "should start to initiate the multi comments line exit", /* name
                                                                  */
        shouldStartToInitiateTheMultiLineCommentsExit,           /* test
                                                                  */
        before_each,                                             /* setup */
        NULL,                                                    /* tear_down */
        MUNIT_TEST_OPTION_NONE,                                  /* options */
        NULL /* parameters */
    },
    {
        "should be able to exit the multi line comments mode", /* name
                                                                */
        shouldBeAbleToExitTheMultiLineCommentsMode,            /* test
                                                                */
        before_each,                                           /* setup */
        NULL,                                                  /* tear_down */
        MUNIT_TEST_OPTION_NONE,                                /* options */
        NULL                                                   /* parameters */
    },
    {
        "should quit initiating the multi line comments exit when the last "
        "char "
        "is not a slash", /* name
                           */
        shouldQuitInitiatingTheMultineCommentsExitWhenTheLastCharIsNotASlash, /* test
                                                                               */
        before_each,            /* setup */
        NULL,                   /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "should print slash anyway in comment mode", /* name
                                                      */
        shouldPrintSlashAnywayWhenInQuoteMode,       /* test
                                                      */
        before_each,                                 /* setup */
        NULL,                                        /* tear_down */
        MUNIT_TEST_OPTION_NONE,                      /* options */
        NULL                                         /* parameters */
    },
    {
        "should print start anyway when in quote mode", /* name
                                                         */
        shouldPrintStarAnywayWhenInQuoteMode,           /* test
                                                         */
        before_each,                                    /* setup */
        NULL,                                           /* tear_down */
        MUNIT_TEST_OPTION_NONE,                         /* options */
        NULL                                            /* parameters */
    },
    {
        "should not print quote when in multi line comments mode", /* name
                                                                    */
        shouldNotPrintQuoteWhenInMultiLineCommentsMode,            /* test
                                                                    */
        before_each,                                               /* setup */
        NULL,                   /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "should not print quote when in  line comment mode", /* name
                                                              */
        shouldNotPrintQuoteWhenInLineCommentMode,            /* test
                                                              */
        before_each,                                         /* setup */
        NULL,                                                /* tear_down */
        MUNIT_TEST_OPTION_NONE,                              /* options */
        NULL                                                 /* parameters */
    },
    {
        "should be able to exit the quote mode",  /* name
                                                   */
        shouldNotPrintQuoteWhenInLineCommentMode, /* test
                                                   */
        before_each,                              /* setup */
        NULL,                                     /* tear_down */
        MUNIT_TEST_OPTION_NONE,                   /* options */
        NULL                                      /* parameters */
    },
    {
        "should be able to exit the quote mode", /* name
                                                  */
        shouldBeAbleToExitTheQuoteMode,          /* test
                                                  */
        before_each,                             /* setup */
        NULL,                                    /* tear_down */
        MUNIT_TEST_OPTION_NONE,                  /* options */
        NULL                                     /* parameters */
    },
    {
        "should not modify the comments state when encoutering a start without "
        "encoutering a slash before", /* name
                                       */
        shouldNotModifyTheCommentsStateWhenEncouteringAStartWitoutHavingEncouterASlashBefore, /* test
                                                                                               */
        before_each,            /* setup */
        NULL,                   /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    /* Mark the end of the array with an entry where the test
     * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/remove-comments ",    /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&suite, (void *)"µnit", argc, argv);
}
