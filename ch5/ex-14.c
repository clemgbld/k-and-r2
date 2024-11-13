#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000    /* max #lines to be sorted */
char *lineptr[MAXLINES]; /* pointers to text lines */
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void quick_sort(void *lineptr[], int left, int right,
                int (*comp)(void *, void *));

int numcmp(char *, char *);
int rnumcmp(char *, char *);
int rstrcmp(char *, char *);
/* sort input lines */
int main(int argc, char *argv[]) {
  int nlines;           /* number of input lines read */
  bool numeric = false; /* 1 if numeric sort */
  bool reverse = false;

  while (--argc > 0 && (*++argv)[0] == '-') {
    switch (*argv[1]) {
    case 'n': {
      numeric = true;
      break;
    }
    case 'r': {
      reverse = true;
      break;
    }
    default: {
      printf("Invalid argument: %s\n", *argv);
      break;
    }
    }
  }

  if (argc > 1 && strcmp(argv[1], "-n") == 0)
    numeric = 1;
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    quick_sort((void **)lineptr, 0, nlines - 1,
               (int (*)(void *, void *))(numeric   ? reverse ? rnumcmp : numcmp
                                         : reverse ? rstrcmp
                                                   : strcmp));
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}

void quick_sort(void *v[], int left, int right, int (*comp)(void *, void *)) {
  int i, last;
  void swap(void *v[], int, int);
  if (left >= right) /* do nothing if array contains */
    return;          /* fewer than two elements */
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
    if ((*comp)(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  quick_sort(v, left, last - 1, comp);
  quick_sort(v, last + 1, right, comp);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2) {
  double v1, v2;
  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  else
    return 0;
}

int rnumcmp(char *s1, char *s2) {
  double v1, v2;
  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2)
    return 1;
  else if (v1 > v2)
    return -1;
  else
    return 0;
}

int rstrcmp(char *s1, char *s2) {
  int cmp = strcmp(s1, s2);
  if (cmp == 1)
    return -1;
  if (cmp == -1)
    return 1;
  return 0;
}

void swap(void *v[], int i, int j) {
  void *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
