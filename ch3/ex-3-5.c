#include <string.h>

void reverse(char s[]) {
  int c, i, j;
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

char convert(unsigned int n, int b) {
  int basedn = n % b;
  if (basedn < 10)
    return basedn + '0';
  return basedn - 10 + 'A';
}

void itob(int n, char s[], int b) {
  int i, sign;
  unsigned int number;
  if ((sign = n) < 0) {
    number = -n;
  } else {
    number = n;
  }
  i = 0;
  if (b == 1) {
    while (n > 0) {
      s[i++] = '1';
      n--;
    }

  } else {
    do {
      s[i++] = convert(number, b);
    } while ((number /= b) > 0);
  }

  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}
