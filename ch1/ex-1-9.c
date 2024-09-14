#include <stdio.h>

int main() {
  int prevC;
  int c = getchar();
  while (c != EOF) {
    if (prevC != ' ' || c != ' ') {
      putchar(c);
    }
    prevC = c;
    c = getchar();
  }

  return 0;
}
