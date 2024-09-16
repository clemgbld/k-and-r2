#include <stdio.h>

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
  const int MAX = 80;
  int len;
  char line[MAXLINE];
  while ((len = getLine(line, MAXLINE)) > 0) {
    if (len > MAX) {
      printf("%s\n", line);
    }
  }

  return 0;
}
