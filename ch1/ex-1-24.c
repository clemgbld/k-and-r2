int isInLineComments(char modes[]) {
  return modes[0] == '/' && modes[1] == '/';
}

void countSyntaxes(char c, int syntaxesCount[], char modes[]) {

  if (c == '/') {
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

  if (c == '*') {
    if (modes[1] == '*') {
      modes[2] = '*';
    } else {
      syntaxesCount[10] = syntaxesCount[10] + 1;
      modes[1] = '*';
    }
  }

  if (c == '(') {
    syntaxesCount[0] = syntaxesCount[0] + 1;
  }
  if (c == ')') {
    syntaxesCount[1] = syntaxesCount[1] + 1;
  }

  if (c == '{' && modes[0] != '"') {
    syntaxesCount[2] = syntaxesCount[2] + 1;
  }

  if (c == '}') {
    syntaxesCount[3] = syntaxesCount[3] + 1;
  }

  if (c == '[') {
    syntaxesCount[4] = syntaxesCount[4] + 1;
  }

  if (c == ']') {
    syntaxesCount[5] = syntaxesCount[5] + 1;
  }

  if (c == '"') {
    if (modes[0] == '"') {
      syntaxesCount[7] = syntaxesCount[7] + 1;
      modes[0] = 0;
    } else {
      syntaxesCount[6] = syntaxesCount[6] + 1;
      modes[0] = '"';
    }
  }

  if (c == '\'') {
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
};
