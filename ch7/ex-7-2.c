#include <stdio.h>

int main() {
  int count = 0;
  int c;
  const int MAX_CHARS_IN_LINE = 76;

  while ((c = getchar()) != EOF) {
    if (c >= 0 && c <= 31) {
      printf("%x", c);
    } else if (c == '\n') {
      printf("%c", c);
      count = 0;
    } else if (count > MAX_CHARS_IN_LINE) {
      printf("%c", '\n');
      printf("%c", c);
      count = 1;
    } else {
      count += 1;
      printf("%c", c);
    }
  }

  return 0;
}
