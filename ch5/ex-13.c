#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000    /* max #lines to be sorted */
#define MAXLEN 1000      /* max length of any input line */
#define MAX 100000       /* max length of any input line */
char *lineptr[MAXLINES]; /* pointers to text lines */
char lines[MAX];

int readlines(char *lineptr[], int nlines, char lines[]);
void writelines(char *lineptr[], int nlines);

int main(int argc, char *argv[]) {
  int const DEFAULT_N = 10;
  int n = DEFAULT_N;

  if (argc - 1 > 0 && (*++argv)[0] == '-') {
    n = atoi(*argv + 1);
  }
  int nlines;
  if ((nlines = readlines(lineptr, MAXLINES, lines)) >= 0) {
    writelines(n >= nlines ? lineptr : lineptr + (nlines - n),
               n >= nlines ? nlines : n);
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
