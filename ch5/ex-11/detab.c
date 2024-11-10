#include <stdio.h>
#include <stdlib.h>

const int TAB_SPACES = 4;

int getTab(int argc, int i, char *argv[]) {
  if (i > argc)
    return TAB_SPACES;
  return atoi(argv[i]);
}

int main(int argc, char *argv[]) {
  int c;
  int i = 0;
  int k = 1;
  int t = getTab(argc, k, argv);
  k++;
  while ((c = getchar()) != EOF) {
    if (k > argc) {
      if (i != 0 && i % TAB_SPACES == 0) {
        t += TAB_SPACES;
      }
    } else {
      if (i != 0 && i == getTab(argc, k, argv)) {
        t += getTab(argc, k, argv);
        k++;
      }
    }
    if (c == '\t') {
      if (i > t) {
        int spaceToAdd = t - i;
        for (int j = 0; j < spaceToAdd; j++) {
          putchar(' ');
          i++;
        }
      }
    } else if (c == '\n') {
      i = 0;
      k = 1;
      t = getTab(argc, k, argv);
      k++;
      putchar(c);
    } else {
      putchar(c);
      i++;
    }
  }

  return 0;
}
