#include <stdio.h>

int main() {
  int c;
  int countSpace = 0;
  int countTab = 0;
  int countNewLine = 0;
  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      ++countSpace;
    } else if (c == '\t') {
      ++countTab;
    } else if (c == '\n') {
      ++countNewLine;
    }
    printf("count space :%d\ncount tabs: %d\ncount new line: %d\n", countSpace,
           countTab, countNewLine);
  }
}
