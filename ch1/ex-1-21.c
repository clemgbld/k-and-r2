#include <stdio.h>

int main() {
  int c;
  int i = 0;
  const int TAB_SPACES = 6;

  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      int numberOfSpaces = 1;
      while ((c = getchar()) == ' ') {
        numberOfSpaces++;
      }
      int spaceToAdd = TAB_SPACES - (i % TAB_SPACES);
      while (spaceToAdd != 0 && spaceToAdd <= numberOfSpaces) {
        putchar('\t');
        i += spaceToAdd;
        numberOfSpaces -= spaceToAdd;
        spaceToAdd = TAB_SPACES - (i % TAB_SPACES);
      }

      while (numberOfSpaces > 0) {
        putchar(' ');
        i++;
        numberOfSpaces--;
      }
      putchar(c);
    } else if (c == '\t') {
      putchar('\t');
      i += TAB_SPACES - (i % TAB_SPACES);
    } else if (c == '\n') {
      i = 0;
      putchar(c);
    } else {
      putchar(c);
      i++;
    }
  }
  return 0;
}
