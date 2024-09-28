#include <stdio.h>

typedef void (*PrintChar)(const char c);

typedef struct {
  PrintChar printChar;
} Logger;

int isInLineCommentMode(char comments[]) {
  return comments[0] == '/' && comments[1] == '/';
}

int isInMultiLineCommentsMode(char comments[]) {
  return comments[0] == '/' && comments[1] == '*';
}

int shouldNotLogCurrentChar(char c, char comments[]) {
  return isInMultiLineCommentsMode(comments) || isInLineCommentMode(comments) ||
         c == '/' && comments[0] != '"';
}

int shoudExitMultiLineCommentsMode(char comments[], char c) {
  return isInMultiLineCommentsMode(comments) && comments[2] == '*' && c == '/';
}

void removeComments(char c, char comments[], Logger *logger) {
  if (c == '/' && comments[0] != '"') {
    if (comments[0] == '/' && comments[1] != '*') {
      comments[1] = c;
    } else {
      comments[0] = c;
    }
  }

  if (c == '*' && comments[0] != '"') {
    if (comments[0] == '/') {
      if (comments[1] == '*') {
        comments[2] = c;
      } else {
        comments[1] = c;
      }
    }
  }

  if (comments[0] == '/' && comments[1] != '*' && comments[1] != '/' &&
      c != '/') {
    comments[0] = 0;
    logger->printChar('/');
  }

  if (isInMultiLineCommentsMode(comments) && comments[2] == '*' && c != '/' &&
      c != '*') {
    comments[2] = 0;
  }

  if (c == '"' && !isInMultiLineCommentsMode(comments) &&
      !isInLineCommentMode(comments)) {
    if (comments[0] == '"') {
      comments[0] = 0;
    } else {
      comments[0] = c;
      comments[1] = 0;
      comments[2] = 0;
    }
  }
  if (shouldNotLogCurrentChar(c, comments)) {
    if (isInLineCommentMode(comments) && c == '\n') {
      comments[0] = 0;
      comments[1] = 0;
      logger->printChar('\n');
    }
    if (shoudExitMultiLineCommentsMode(comments, c)) {
      comments[0] = 0;
      comments[1] = 0;
      comments[2] = 0;
    }
    return;
  }
  logger->printChar(c);
}

void printChar(char c) { putchar(c); };

int main() {
  Logger logger;

  logger.printChar = printChar;

  int c;
  char comments[4] = {0, 0, 0, 0};
  while ((c = getchar()) != EOF) {
    removeComments(c, comments, &logger);
  }

  return 0;
}
