#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  const int TAB_SPACES = 4;
  int initialT = TAB_SPACES;
  int c;
  int i = 0;
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
      initialT = atoi(num);
      break;
    }
    default: {
      printf("find: illegal option %c\n", c);
      return 1;
    }
    }
  }
  int t = initialT;
  while ((c = getchar()) != EOF) {
    if (i != 0 && (i - m) % initialT == 0 && i > m) {
      t += initialT;
    }
    if (c == '\t' && i > m) {
      int spaceToAdd = t - (i - m);
      for (int j = 0; j < spaceToAdd; j++) {
        putchar(' ');
        i++;
      }
    } else if (c == '\n') {
      i = 0;
      t = initialT;
      putchar(c);
    } else {
      putchar(c);
      i++;
    }
  }

  return 0;
}
