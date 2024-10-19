#include <string.h>

void reverse(char s[]) {
  int c, i, j;
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void itoa(int n, char s[], int width) {
  int i, sign;
  unsigned int number;
  if ((sign = n) < 0) {
    number = -n;
  } else {
    number = n;
  }
  i = 0;
  do {
    s[i++] = number % 10 + '0';
  } while ((number /= 10) > 0);
  if (sign < 0)
    s[i++] = '-';

  while (i < width) {
    s[i++] = ' ';
  }

  s[i] = '\0';
  reverse(s);
}
