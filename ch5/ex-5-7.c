#include <stdio.h>
#include <string.h>

#define MAXLINES 5000    /* max #lines to be sorted */
#define MAXLEN 1000      /* max length of any input line */
#define MAX 100000       /* max length of any input line */
char *lineptr[MAXLINES]; /* pointers to text lines */
char lines[MAX];

int readlines(char *lineptr[], int nlines, char lines[]);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);
/* sort input lines */
int main() {
  int nlines; /* number of input lines read */
  if ((nlines = readlines(lineptr, MAXLINES, lines)) >= 0) {
    qsort(lineptr, 0, nlines - 1);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
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

char *alloc(int);
/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char *lines) {
  int len, nlines;
  nlines = 0;
  while ((len = getLine(lines, MAXLEN)) > NULL) {
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

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
  int i;
  for (i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right) {
  int i, last;
  void swap(char *v[], int i, int j);
  if (left >= right) /* do nothing if array contains */
    return;          /* fewer than two elements */
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
    if (strcmp(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  qsort(v, left, last - 1);
  qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j) {
  char *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
