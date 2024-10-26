#include <stdio.h>

char buf = 0;   /* buffer for ungetch */
int getch(void) /* get a (possibly pushed-back) character */
{
  if (buf != 0) {
    char tmp = buf;
    buf = 0;
    return tmp;
  }
  return getchar();
}
void ungetch(int c) /* push character back on input */
{
  if (buf != 0)
    printf("ungetch: too many characters\n");
  else
    buf = c;
}
