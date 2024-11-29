#include <ctype.h>
#include <stdio.h>

#define MAXWORD 100

int getword(char *, int);

int main() {

  char word[MAXWORD];

  while (getword(word, MAXWORD) != EOF) {
    printf("%s\n", word);
  }

  return 0;
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
  int c, getch(void);
  void ungetch(int);
  char *w = word;
  while (isspace(c = getch()))
    ;

  if (c == '/') {
    int potentialNextSlash = getch();
    if (potentialNextSlash == '/') {
      while ((c = getch()) != '\n')
        ;
      while (isspace(c = getch()))
        ;
    } else {
      ungetch(potentialNextSlash);
    }
  }

  if (c != EOF)
    *w++ = c;

  if (!isalpha(c) && c != '"') {
    *w = '\0';
    return c;
  }

  int isStringConstant = c == '"';

  if (isStringConstant) {
    for (; --lim > 0; w++) {
      *w = getch();
      if (*w == '"') {
        w++;
        break;
      }
    }

  } else {
    for (; --lim > 0; w++)
      if (!isalnum(*w = getch()) && *w != '_') {
        ungetch(*w);
        break;
      }
  }

  *w = '\0';
  return word[0];
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
