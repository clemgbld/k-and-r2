#include <stdio.h>

int main() {
  int lim = 1000;
  int c;
  char s[lim];
  int i;
  for (i = 0; i < lim - 1 ? (c = getchar()) != '\n' ? c != EOF : 0 : 0; i++) {
    s[i] = c;
  }
  return 0;
}
