#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *padEnd(char *str) {

  int i = strlen(str) - 1;

  while (str[i] == ' ' || str[i] == '\t') {
    i--;
  }

  char *paddedEnd = malloc(i + 1);

  strncpy(paddedEnd, str, i + 1);

  paddedEnd[i + 1] = '\0';

  return paddedEnd;
}

int getLine(char s[], int limit) {
  int c, i;

  for (int i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    s[i] = c;
  }

  if (c == '\n') {
    s[i] = c;
    i++;
  }

  s[i] = '\0';
  return i;
}

int main() {
  const int MAXLINE = 1000;
  int len;
  char line[MAXLINE];
  while ((len = getLine(line, MAXLINE)) > 0) {
    char *paddedEndLine = padEnd(line);
    printf("%s\n", paddedEndLine);
    free(paddedEndLine);
  }
  return 0;
}
