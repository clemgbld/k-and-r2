#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int strindex(char *s, char *t) {
  for (int i = 0; *s != '\0'; s++) {
    char *sbegin = s;
    char *tbegin = t;
    for (; *tbegin != '\0' && *sbegin == *tbegin; sbegin++, tbegin++)
      ;
    if (tbegin > t && *tbegin == '\0')
      return i;
    i++;
  }
  return -1;
}

int atoiCustom(char *s) {
  int i, n;
  n = 0;
  for (; *s >= '0' && *s <= '9'; s++)
    n = 10 * n + (*s - '0');
  return n;
}

void reverse(char *s) {
  char c;
  for (char *end = s + strlen(s) - 1; s < end; s++, end--) {
    c = *s;
    *s = *end;
    *end = c;
  }
}

void itoa(int n, char *s) {
  int i, sign;
  unsigned int number;
  char *begin = s;
  if ((sign = n) < 0) {
    number = -n;
  } else {
    number = n;
  }
  i = 0;
  do {
    *s++ = number % 10 + '0';
  } while ((number /= 10) > 0);
  if (sign < 0) {
    *s++ = '-';
  }

  *s = '\0';
  reverse(begin);
}

char convert(unsigned int n, int b) {
  int basedn = n % b;
  if (basedn < 10)
    return basedn + '0';
  return basedn - 10 + 'A';
}

void itob(int n, char *s, int b) {
  int i, sign;
  unsigned int number;
  char *begin = s;
  if ((sign = n) < 0) {
    number = -n;
  } else {
    number = n;
  }
  if (b == 1) {
    while (n > 0) {
      *s++ = '1';
      n--;
    }

  } else {
    do {
      *s++ = convert(number, b);
    } while ((number /= b) > 0);
  }

  if (sign < 0)
    *s++ = '-';
  *s = '\0';
  reverse(begin);
}

double atofcustom(char *s) {
  double val, power;
  double exp = 0;
  int sign;
  for (; isspace(*s); s++)
    ;
  sign = (*s == '-') ? -1 : 1;
  if (*s == '+' || *s == '-')
    s++;
  for (val = 0.0; isdigit(*s); s++)
    val = 10.0 * val + (*s - '0');
  if (*s == '.')
    s++;
  for (power = 1.0; isdigit(*s); s++) {
    val = 10.0 * val + (*s - '0');
    power *= 10;
  }

  double result = sign * val / power;

  if (*s == 'e' || *s == 'E') {
    s++;
  }

  if (*s == '-') {
    sign = -1;
    s++;
  } else {
    if (*s == '+')
      s++;
    sign = 1;
  }

  if (isdigit(*s)) {
    for (; isdigit(*s); s++) {
      exp = 10 * exp + (*s - '0');
    }
    result = result * pow(10, sign * exp);
  }

  return result;
}

int getLine(char *s, int limit) {
  int c;
  char *begin = s;

  for (; (s - begin) < limit - 1 && (c = getchar()) != EOF && c != '\n'; s++) {
    *s = c;
  }

  if (c == '\n') {
    *s = c;
    s++;
  }

  *s = '\0';
  return s - begin;
}

#define NUMBER '0'

int getch(void);

int getop(char *s) {
  static int c_buf = 0;

  int i, c;
  if (c_buf == 0) {
    c = getch();
  } else {
    c = c_buf;
    c_buf = 0;
  }

  while ((*s = c) == ' ' || c == '\t')
    c = getch();
  ;
  *(s + 1) = '\0';
  if (!isdigit(c) && c != '.')
    return c;     /* not a number */
  if (isdigit(c)) /* collect integer part */
    while (isdigit(*++s = c = getch()))
      ;
  if (c == '.') /* collect fraction part */
    while (isdigit(*++s = c = getch()))
      ;
  *s = '\0';
  if (c != EOF)
    c_buf = c;
  return NUMBER;
}

#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */
int getch(void)    /* get a (possibly pushed-back) character */
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}
