#include <stdio.h>

int main() {
  int lim = 1000;
  int c;
  char s[lim];
  int i;
  for (i = 0; i < lim - 1 ? 0 : (c = getchar()) != '\n' ? 1 : c != EOF; i++) {
    s[i] = c;
  }
  return 0;
}
