#include <stdio.h>
#include <string.h>

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

/* it is way more flexible if ungetechs does not about buf and bufp like that we
 * can put into the buffer one or many chars*/
void ungets(char s[]) {
  for (int i = strlen(s); i >= 0; i--) {
    ungetch(s[i]);
  }
}
