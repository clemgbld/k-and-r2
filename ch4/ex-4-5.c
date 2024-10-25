#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXOP 100
#define NUMBER '0'
#define SINUS '1'
const char EXP = '2';
const char POW = '3';

int getop(char[]);
void push(double);
double pop(void);
int isempty(void);

int main() {
  int type;
  double op2;
  char s[MAXOP];
  double sign = 1;
  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(s) * sign);
      sign = 1;
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      if (isempty()) {
        sign = -1;
        break;
      }
      op2 = pop();
      if (isempty()) {
        push(op2);
        sign = -1;
        break;
      }
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
        push(pop() / op2);
      else
        printf("error: zero divisor\n");
      break;
    case '%':
      op2 = pop();
      if (op2 != 0.0)
        push(fmod(pop(), op2));
      else
        printf("error: zero divisor\n");
      break;
    case SINUS:
      push(sin(pop()));
      break;
    case EXP:
      push(exp(pop()));
      break;
    case POW:
      op2 = pop();
      push(pow(pop(), op2));
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }
  return 0;
}

#define MAXVAL 100
int sp = 0;
double val[MAXVAL];

int isempty(void) { return sp == 0; }

void push(double f) {
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

int getch(void);
void ungetch(int);

int getop(char s[]) {
  int i, c;
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';

  if (!isdigit(c) && c != '.' && c != 's' && c != 'e' && c != 'p')
    return c; /* not a number */

  i = 0;

  if (c == 's' || c == 'e' || c == 'p') {
    if (c == 's') {
      s[++i] = c = getch();
      if (c == 'i') {
        s[++i] = c = getch();
        if (c == 'n') {
          s[i] = '\0';
          return SINUS;
        } else {
          ungetch(s[1]);
          ungetch(c);
          s[1] = '\0';
          return s[0];
        }
      } else {
        s[1] = '\0';
        ungetch(c);
        return s[0];
      }
    } else if (c == 'e') {
      s[++i] = c = getch();
      if (c == 'x') {
        s[++i] = c = getch();
        if (c == 'p') {
          s[i] = '\0';
          return EXP;
        } else {
          ungetch(s[1]);
          ungetch(c);
          s[1] = '\0';
          return s[0];
        }
      } else {
        s[1] = '\0';
        ungetch(c);
        return s[0];
      }
    } else if (c == 'p') {
      s[++i] = c = getch();
      if (c == 'o') {
        s[++i] = c = getch();
        if (c == 'w') {
          s[i] = '\0';
          return POW;
        } else {
          ungetch(s[1]);
          ungetch(c);
          s[1] = '\0';
          return s[0];
        }
      } else {
        s[1] = '\0';
        ungetch(c);
        return s[0];
      }
    }
  }

  i = 0;

  if (isdigit(c)) /* collect integer part */
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.') /* collect fraction part */
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if (c != EOF)
    ungetch(c);
  return NUMBER;
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
