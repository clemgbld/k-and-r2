#include <stdio.h>

int isInLineComments(char modes[]) {
  return modes[0] == '/' && modes[1] == '/';
}

int isInMultiComments(char modes[]) {
  return modes[0] == '/' && modes[1] == '*';
}

void countSyntaxes(char c, int syntaxesCount[], char modes[]) {

  if (c == '/' && modes[0] != '"' && modes[0] != '\'') {
    if (modes[0] == '/' && modes[2] == '*') {
      syntaxesCount[11] = syntaxesCount[11] + 1;
      modes[0] = 0;
      modes[1] = 0;
      modes[2] = 0;
    } else if (modes[0] == '/' && modes[1] != '*') {
      modes[1] = '/';
    } else {
      modes[0] = '/';
    }
  }

  if (modes[2] == '*' && c != '/') {
    modes[2] = 0;
  }

  if (c == '*' && !isInLineComments(modes)) {
    if (modes[1] == '*') {
      modes[2] = '*';
    } else if (modes[0] == '/') {
      syntaxesCount[10] = syntaxesCount[10] + 1;
      modes[1] = '*';
    }
  }

  if (c == '(' && modes[0] != '"' && modes[0] != '\'' &&
      !isInMultiComments(modes) && !isInLineComments(modes)) {
    syntaxesCount[0] = syntaxesCount[0] + 1;
  }
  if (c == ')' && modes[0] != '"' && modes[0] != '\'' &&
      !isInMultiComments(modes) && !isInLineComments(modes)) {
    syntaxesCount[1] = syntaxesCount[1] + 1;
  }

  if (c == '{' && modes[0] != '"' && modes[0] != '\'' &&
      !isInMultiComments(modes) && !isInLineComments(modes)) {
    syntaxesCount[2] = syntaxesCount[2] + 1;
  }

  if (c == '}' && modes[0] != '"' && modes[0] != '\'' &&
      !isInMultiComments(modes) && !isInLineComments(modes)) {
    syntaxesCount[3] = syntaxesCount[3] + 1;
  }

  if (c == '[' && modes[0] != '"' && modes[0] != '\'' &&
      !isInMultiComments(modes) && !isInLineComments(modes)) {
    syntaxesCount[4] = syntaxesCount[4] + 1;
  }

  if (c == ']' && modes[0] != '"' && modes[0] != '\'' &&
      !isInMultiComments(modes) && !isInLineComments(modes)) {
    syntaxesCount[5] = syntaxesCount[5] + 1;
  }

  if (c == '"' && modes[0] != '\'' && !isInMultiComments(modes) &&
      !isInLineComments(modes) && modes[3] != '\\') {
    if (modes[0] == '"') {
      syntaxesCount[7] = syntaxesCount[7] + 1;
      modes[0] = 0;
    } else {
      syntaxesCount[6] = syntaxesCount[6] + 1;
      modes[0] = '"';
    }
  }

  if (c == '\'' && modes[0] != '"' && !isInMultiComments(modes) &&
      !isInLineComments(modes) && modes[3] != '\\') {
    if (modes[0] == '\'') {
      syntaxesCount[9] = syntaxesCount[9] + 1;
      modes[0] = 0;
    } else {
      syntaxesCount[8] = syntaxesCount[8] + 1;
      modes[0] = '\'';
    }
  }

  if (c == '\n' && isInLineComments(modes)) {
    modes[0] = 0;
    modes[1] = 0;
  }

  if (modes[3] == '\\') {
    modes[3] = 0;
  }

  if (c == '\\') {
    modes[3] = '\\';
  }
};

int main() {
  int syntaxesCount[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  char modes[4] = {0, 0, 0, 0};
  int c;

  while ((c = getchar()) != EOF) {
    countSyntaxes(c, syntaxesCount, modes);
  }

  char *messages[12] = {" parenthesis ",      " parenthesis ",
                        " curly brackets ",   " curly brackets ",
                        " squared brackets ", " squared brackets ",
                        " double quotes ",    " double quotes ",

                        " single quotes ",    " single quotes ",
                        " comments ",         " comments "};

  for (int i = 0; i < 12; i += 2) {
    if (syntaxesCount[i] != syntaxesCount[i + 1]) {
      printf("%s%s%s", "Unbalenced", messages[i], "at the end of the file\n");
    }
  }

  return 0;
}
