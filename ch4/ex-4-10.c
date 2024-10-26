#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXOP 100
#define NUMBER '0'
#define SINUS '1'
const char EXP = '2';
const char POW = '3';

void push(double);
double pop(void);
int isempty(void);

int getLine(char s[], int limit) {
  int c, i;

  for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    s[i] = c;
  }

  if (c == '\n') {
    s[i] = c;
    i++;
  }

  s[i] = '\0';
  return i;
}

int main() {
  int type;
  double op2;
  char s[MAXOP];
  double sign = 1;
  const int MAXLINE = 1000;
  int len;
  char line[MAXLINE];
  while ((len = getLine(line, MAXLINE)) > 0) {
    for (int i = 0; i <= len; i++) {
      int j = 0;
      if (line[i] == ' ' || line[i] == '\t') {
        continue;
      }
      if (isdigit(line[i]) || line[i] == '.') {
        for (; isdigit(line[i]); i++, j++) {
          s[j] = line[i];
        };
        if (line[i] == '.') {
          s[++j] = line[++i];
          for (; isdigit(line[i]); i++, j++) {
            s[j] = line[i];
          };
        }

        s[j] = '\0';
        push(atof(s) * sign);
        sign = 1;
        continue;
      }

      if (line[i] == '%') {
        op2 = pop();
        if (op2 != 0.0)
          push(fmod(pop(), op2));
        else
          printf("error: zero divisor\n");
      }

      if (line[i] == '/') {
        op2 = pop();
        if (op2 != 0.0)
          push(pop() / op2);
        else
          printf("error: zero divisor\n");
        continue;
      }

      if (line[i] == '+') {
        push(pop() + pop());
        continue;
      }

      if (line[i] == '*') {
        push(pop() + pop());
        continue;
      }

      if (line[i] == '-') {
        if (isempty()) {
          sign = -1;
          continue;
        }
        op2 = pop();
        if (isempty()) {
          push(op2);
          sign = -1;
          continue;
        }
        push(pop() - op2);
      }
    }
    printf("\t%.8g\n", pop());
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
