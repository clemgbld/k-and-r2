#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER '0'

int getch(void);

int getop(char s[]) {
  static int c_buf = 0;

  int i, c;
  if (c_buf == 0) {
    c = getch();
  } else {
    c = c_buf;
    c_buf = 0;
  }

  while ((s[0] = c) == ' ' || c == '\t')
    c = getch();
  ;
  s[1] = '\0';
  if (!isdigit(c) && c != '.')
    return c; /* not a number */
  i = 0;
  if (isdigit(c)) /* collect integer part */
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.') /* collect fraction part */
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
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
