#include <string.h>

void reverse(char s[]) {
  int c, i, j;
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

// the bug was happening because of this line n = -n because 2147483648 made
// postive is bigger than than the signed int max range which is 2147483647
// to fix it we can use an unsigned int who have the max range of 4294967295 or
// treat the min range as a special edege case and make the conversion manually

void itoa(int n, char s[]) {
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
  s[i] = '\0';
  reverse(s);
}
