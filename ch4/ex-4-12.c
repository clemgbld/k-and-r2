#include <string.h>

void reverse(char s[]) {
  int c, i, j;
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void itoaRecur(unsigned int n, char s[], int i, int sign) {
  if (n / 10 > 0) {
    int newN = n / 10;
    s[i] = newN % 10 + '0';
    return itoaRecur(newN, s, i + 1, sign);
  }
  if (sign < 0) {
    s[i++] = '-';
  }
  s[i] = '\0';
  reverse(s);
}

void itoa(int n, char s[]) {
  unsigned int number;
  int sign;
  if ((sign = n) < 0) {
    number = -n;
  } else {
    number = n;
  }
  s[0] = number % 10 + '0';
  itoaRecur(number, s, 1, sign);
}
