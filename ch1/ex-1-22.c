#include <stdio.h>

int findIndexToBreak(char str[], int start, int interval) {
  int i = start;
  int lastSpaceToBreak = -1;
  while (str[i] != '\0') {
    if ((i - start) > interval && lastSpaceToBreak != -1) {
      return lastSpaceToBreak;
    }

    if (str[i] == ' ' || str[i] == '\t') {
      lastSpaceToBreak = i;
    }

    i++;
  }

  if ((i - start) > interval) {
    return interval + start;
  }

  if (str[i] == '\0') {
    return -1;
  }

  return lastSpaceToBreak;
}

int getLine(char s[], int limit) {
  int c, i;

  for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
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
  const int INTERVAL = 20;

  char line[MAXLINE];
  int i = 0;
  int len = getLine(line, MAXLINE);
  int indexToBreak = findIndexToBreak(line, i, INTERVAL);

  while (i < len) {
    if (indexToBreak == i) {
      if (line[i] == ' ' || line[i] == '\t') {
        printf("\n");
        indexToBreak = findIndexToBreak(line, i, INTERVAL);
      } else {
        printf("%c", line[i]);
        printf("\n");
        indexToBreak = findIndexToBreak(line, i + 1, INTERVAL);
      }
    } else {
      printf("%c", line[i]);
    }
    i++;
  }

  printf("\n");

  return 0;
}
