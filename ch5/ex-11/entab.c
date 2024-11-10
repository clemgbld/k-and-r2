#include <stdio.h>
#include <stdlib.h>

const int TAB_SPACES = 6;

int main(int argc, char *argv[]) {
  int c;
  int i = 0;
  int j = 1;

  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      int numberOfSpaces = 1;
      while ((c = getchar()) == ' ') {
        numberOfSpaces++;
      }
      int spaceToAdd = j < argc ? atoi(argv[j]) : TAB_SPACES - (i % TAB_SPACES);
      if (j < argc) {
        j++;
      }
      while (spaceToAdd != 0 && spaceToAdd <= numberOfSpaces) {
        putchar('\t');
        i += spaceToAdd;
        numberOfSpaces -= spaceToAdd;
        spaceToAdd = j < argc ? atoi(argv[j]) : TAB_SPACES - (i % TAB_SPACES);
        if (j < argc) {
          j++;
        }
      }

      while (numberOfSpaces > 0) {
        putchar(' ');
        i++;
        numberOfSpaces--;
      }
      putchar(c);
    } else if (c == '\t') {
      putchar('\t');
      i += j < argc ? atoi(argv[j]) : TAB_SPACES - (i % TAB_SPACES);
      if (j < argc) {
        j++;
      }
    } else if (c == '\n') {
      i = 0;
      j = 1;
      putchar(c);
    } else {
      putchar(c);
      i++;
    }
  }
  return 0;
}
