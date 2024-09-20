#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *reverse(char *str) {

  int length = strlen(str);

  char *reversed = malloc(length + 1);

  int i = length - 1;
  int j = 0;

  while (i != -1) {
    reversed[j] = str[i];
    i--;
    j++;
  }

  reversed[j] = '\0';

  return reversed;
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
    char *reversedLine = reverse(line);
    printf("%s\n", reversedLine);
    free(reversedLine);
  }
  return 0;
}
