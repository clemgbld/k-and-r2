#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int c;
  int i = 0;
  const int TAB_SPACES = 6;
  int tabSpaces = TAB_SPACES;
  int m = 0;
  while (--argc > 0 && ((*++argv)[0] == '-' || *argv[0] == '+')) {
    char c = *argv[0];
    char *num = (*argv + 1);
    switch (c) {
    case '-': {
      m = atoi(num);
      break;
    }
    case '+': {
      tabSpaces = atoi(num);
      break;
    }
    default: {
      printf("find: illegal option %c\n", c);
      return 1;
    }
    }
  }

  while ((c = getchar()) != EOF) {
    if (c == ' ' && i > m) {
      int numberOfSpaces = 1;
      while ((c = getchar()) == ' ') {
        numberOfSpaces++;
      }
      int spaceToAdd = tabSpaces - ((i - m) % tabSpaces);
      while (spaceToAdd != 0 && spaceToAdd <= numberOfSpaces) {
        putchar('\t');
        i += spaceToAdd;
        numberOfSpaces -= spaceToAdd;
        spaceToAdd = tabSpaces - ((i - m) % tabSpaces);
      }

      while (numberOfSpaces > 0) {
        putchar(' ');
        i++;
        numberOfSpaces--;
      }
      putchar(c);
    } else if (c == '\t' && i > m) {
      putchar('\t');
      i += tabSpaces - ((i - m) % tabSpaces);
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
