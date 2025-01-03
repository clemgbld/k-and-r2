#include "./utils/lowercase.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000    /* max #lines to be sorted */
#define MAXLEN 1000      /* max #lines to be sorted */
char *lineptr[MAXLINES]; /* pointers to text lines */
char lines[10000];

int readlines(char *lineptr[], int nlines, char *lines);
void writelines(char *lineptr[], int nlines);
void quick_sort(void *lineptr[], int left, int right,
                int (*comp)(void *, void *));

int numcmp(char *, char *);
int rnumcmp(char *, char *);
int rstrcmp(char *, char *);
int foldstrcmp(char *, char *);
int foldresversestrcmp(char *, char *);
/* sort input lines */
int main(int argc, char *argv[]) {
  int nlines;           /* number of input lines read */
  bool numeric = false; /* 1 if numeric sort */
  bool reverse = false;
  bool fold = false;

  while (--argc > 0 && (*++argv)[0] == '-') {
    int c;
    while (c = *++argv[0]) {
      switch (c) {
      case 'n': {
        numeric = true;
        break;
      }
      case 'r': {
        reverse = true;
        break;
      }
      case 'f': {
        fold = true;
        break;
      }
      default: {
        printf("Invalid argument: %s\n", *argv);
        break;
      }
      }
    }
  }

  if ((nlines = readlines(lineptr, MAXLINES, lines)) >= 0) {
    quick_sort((void **)lineptr, 0, nlines - 1,
               (int (*)(void *, void *))(numeric   ? reverse ? rnumcmp : numcmp
                                         : reverse ? fold ? foldresversestrcmp
                                                          : rstrcmp
                                         : fold    ? foldstrcmp
                                                   : strcmp));
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}

int getLine(char s[], int lim) {
  int c, i;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;
  if (c == '\n' && i != 0) {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}

int readlines(char *lineptr[], int maxlines, char *lines) {
  int len, nlines;
  nlines = 0;
  while ((len = getLine(lines, MAXLEN)) > 0) {
    if (nlines >= maxlines)
      return -1;
    else {
      *(lines + (len - 1)) = '\0';
      lineptr[nlines++] = lines;
      lines += len;
    }
  }

  return nlines;
}

void writelines(char *lineptr[], int nlines) {
  int i;
  for (i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
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

int rnumcmp(char *s1, char *s2) { return numcmp(s2, s1); }

int rstrcmp(char *s1, char *s2) { return strcmp(s2, s1); }

int foldstrcmp(char *s1, char *s2) {
  char *lowereds1 = lowercase(s1);
  char *lowereds2 = lowercase(s2);
  int result = strcmp(lowereds1, lowereds2);
  free(lowereds1);
  free(lowereds2);
  return result;
}

int foldresversestrcmp(char *s1, char *s2) {
  char *lowereds1 = lowercase(s1);
  char *lowereds2 = lowercase(s2);
  int result = strcmp(lowereds2, lowereds1);
  free(lowereds1);
  free(lowereds2);
  return result;
}

void swap(void *v[], int i, int j) {
  void *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
