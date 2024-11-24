#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define MAXTOKEN 100
enum { NAME, PARENS, BRACKETS, ERROR_BRACKET };
void dcl(void);
void dirdcl(void);
int gettoken(void);
int tokentype;           /* type of last token */
char token[MAXTOKEN];    /* last token string */
char name[MAXTOKEN];     /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc. */
char out[1000];
int errorToken = 0;
int main() /* convert declaration to words */
{
  while (gettoken() != EOF) { /* 1st token on line */

    strcpy(datatype, token); /* is the datatype */
    out[0] = '\0';
    dcl(); /* parse rest of line */
    if (errorToken == ERROR_BRACKET) {
      printf("missing ]\n");
      while (gettoken() != '\n')
        ;
      errorToken = 0;
      continue;
    }
    if (tokentype != '\n') {
      if (tokentype == '(') {
        printf("missing )\n");
        while (gettoken() != '\n')
          ;
        continue;
      }
      printf("syntax error\n");
    }
    printf("%s: %s %s\n", name, out, datatype);
  }
  return 0;
}

/* dcl: parse a declarator */
void dcl(void) {
  int ns;
  for (ns = 0; gettoken() == '*';) /* count *'s */
    ns++;
  dirdcl();
  while (ns-- > 0)
    strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void) {
  if (errorToken != 0)
    return;
  int type;
  if (tokentype == '(') { /* ( dcl ) */
    dcl();
    if (errorToken != 0)
      return;
    if (tokentype != ')')
      printf("error: missing )\n");
  } else if (tokentype == NAME) /* variable name */
    strcpy(name, token);
  else
    printf("error: expected name or (dcl)\n");
  while ((type = gettoken()) == PARENS || type == BRACKETS)
    if (type == PARENS)
      strcat(out, " function returning");
    else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
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

int gettoken(void) /* return next token */
{
  int c, getch(void);
  void ungetch(int);
  char *p = token;
  while ((c = getch()) == ' ' || c == '\t')
    ;
  if (c == '(') {
    if ((c = getch()) == ')') {
      strcpy(token, "()");
      return tokentype = PARENS;
    } else {
      ungetch(c);
      tokentype = '(';
      return tokentype;
    }
  } else if (c == '[') {
    for (*p++ = c; (*p++ = getch()) != ']';) {
      if (*p == '\0') {
        errorToken = ERROR_BRACKET;
        return tokentype = ERROR_BRACKET;
      }
    };

    *p = '\0';
    return tokentype = BRACKETS;
  } else if (isalpha(c)) {
    for (*p++ = c; isalnum(c = getch());)
      *p++ = c;
    *p = '\0';
    ungetch(c);
    return tokentype = NAME;
  } else
    return tokentype = c;
}
