#include <stdio.h>

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

void printTopElements(void) {
  for (int i = sp - 1; i >= 0; i--) {
    printf("%f\n", val[i]);
  }
}

void duplicate(double copy[]) {
  for (int i = sp - 1; i >= 0; i--) {
    copy[i] = val[i];
  }
}

void swapTopTwoElements(void) {
  if (sp > 1) {
    int i = sp - 1;
    double temp = val[i];
    val[i] = val[i - 1];
    val[i - 1] = temp;
  }
}

void clear(void) { sp = 0; }
