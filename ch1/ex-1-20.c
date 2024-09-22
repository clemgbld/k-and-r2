#include <stdio.h>

int main() {
  const int TAB_SPACES = 4;
  int c;
  int i = 0;
  int t = TAB_SPACES;

  while ((c = getchar()) != EOF) {
    if (i != 0 && i % 4 == 0) {
      t += TAB_SPACES;
    }
    if (c == '\t') {
      int spaceToAdd = t - i;
      for (int j = 0; j < spaceToAdd; j++) {
        putchar(' ');
        i++;
      }
    } else if (c == '\n') {
      i = 0;
      t = TAB_SPACES;
      putchar(c);
    } else {
      putchar(c);
      i++;
    }
  }

  return 0;
}
