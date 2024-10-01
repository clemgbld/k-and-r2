void countSyntaxes(char c, int syntaxesCount[], char modes[]) {
  if (c == '(') {
    syntaxesCount[0] = syntaxesCount[0] + 1;
  }
  if (c == ')') {
    syntaxesCount[1] = syntaxesCount[1] + 1;
  }

  if (c == '{') {
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
    syntaxesCount[6] = syntaxesCount[6] + 1;
    modes[0] = '"';
  }
};
