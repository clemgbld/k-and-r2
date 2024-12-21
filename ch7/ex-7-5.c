#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXOP 100
#define NUMBER '0'

int getop(char[]);
void push(double);
double pop(void);
int isempty(void);

int main() {
  int c;
  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      printf("\t%.8g\n", pop());
    } else {
      ungetc(c, stdin);
    }

    double num;
    int n = scanf("%lf", &num);

    if (n == 1) {
      push(num);
      continue;
    }

    char type;
    n = scanf(" %c", &type);
    if (n == EOF) {
      break;
    }
    switch (type) {
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-': {
      double op2 = pop();
      push(pop() - op2);
      break;
    }

    case '/': {
      double op2 = pop();
      if (op2 != 0.0)
        push(pop() / op2);
      else
        printf("error: zero divisor\n");
      break;
    }
    case '%': {
      double op2 = pop();
      if (op2 != 0.0)
        push(fmod(pop(), op2));
      else
        printf("error: zero divisor\n");
      break;
    }
    default:
      printf("error: unknown command %c\n", type);
      break;
    }
  }

  return 0;
}

#define MAXVAL 100
int sp = 0;
double val[MAXVAL];

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
