#include <ctype.h>
#include <math.h>
#include <stdio.h>

int getch(void);
void ungetch(int);
/* getint: get next integer from input into *pn */
int getint(double *pn) {
  int c, sign;
  while (isspace(c = getch())) /* skip white space */
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c); /* it is not a number */
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-') {
    c = getch();
    if (!isdigit(c)) {
      ungetch(c);
      ungetch(sign == 1 ? '+' : '-');
      return 0;
    }
  }

  for (*pn = 0.0; isdigit(c); c = getch())
    *pn = 10.0 * *pn + (c - '0');
  if (c == '.') {
    c = getch();
  }
  double power = 1.0;
  for (; isdigit(c); c = getch()) {
    *pn = 10.0 * *pn + (c - '0');
    power *= 10;
  }

  *pn = sign * *pn / power;

  if (c == 'e' || c == 'E') {
    char e = c;
    c = getch();

    if (c == '-') {
      c = getch();
      if (!isdigit(c)) {
        ungetch(c);
        ungetch('-');
        ungetch(e);
        return e;
      }
      sign = -1;
    } else if (c == '+') {
      c = getch();
      if (!isdigit(c)) {
        ungetch(c);
        ungetch('+');
        ungetch(e);
        return e;
      }
      sign = 1;
    } else if (isdigit(c)) {
      sign = 1;
    } else {
      ungetch(c);
      ungetch(e);
      return e;
    }

    double exp = 0;
    for (; isdigit(c); c = getch()) {
      exp = 10 * exp + (c - '0');
    }
    *pn = *pn * pow(10, sign * exp);
  }

  if (c != EOF)
    ungetch(c);
  return c;
}

int main() {
  double pn = 5;
  getint(&pn);
  printf("%f\n", pn);
  return 0;
}

#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */
int getch(void)    /* get a (possibly pushed-back) character */
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) /* push character back on input */
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
