#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXOP 100
#define NUMBER '0'

int getop(char[], char[]);
void push(double);
double pop(void);
int isempty(void);

int main(int argc, char *argv[]) {
  int type;
  double op2;
  char s[MAXOP];
  double sign = 1;
  for (int i = 1; i < argc; i++) {
    type = getop(s, argv[i]);
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
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }

  printf("\t%.8g\n", pop());
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

int getop(char s[], char arg[]) {
  int i = 0;
  int j = 0;
  int c = arg[0];
  if (!isdigit(c) && c != '.')
    return c; /* not a number */
  s[i] = c;
  if (isdigit(c)) /* collect integer part */
    while (arg[j] != '\0' && isdigit(s[++i] = c = arg[++j]))
      ;
  if (c == '.') /* collect fraction part */
    while (arg[j] != '\0' && isdigit(s[++i] = c = arg[++j]))
      ;
  s[i] = '\0';
  return NUMBER;
}
