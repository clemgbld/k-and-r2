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

void copy(char to[], char from[]) {
  int i = 0;
  while ((to[i] = from[i]) != '\0') {
    i++;
  }
}

int main() {
  const int MAXLINE = 1000;
  int len;
  char line[MAXLINE];
  char longest[MAXLINE];

  int max = 0;
  while ((len = getLine(line, MAXLINE)) > 0) {
    if (len > max) {
      max = len;
      copy(longest, line);
    }
    printf("%d\n", len);
  }

  if (max > 0) {
    printf("%s\n", longest);
  }
  return 0;
}
