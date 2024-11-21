#include "./utils/directorystr.h"
#include "./utils/extractfields.h"
#include "./utils/lowercase.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct FieldSort {
  int start;
  int end;
  bool numeric;
  bool reverse;
  bool fold;
  bool directory;
};

#define MAXLINES 5000
#define MAXLEN 1000
#define MAXFIELDS 1000
char *lineptr[MAXLINES];
char lines[10000];
struct FieldSort fields[MAXFIELDS];

int readlines(char *lineptr[], int nlines, char *lines);
void writelines(char *lineptr[], int nlines);
void quick_sort(void *lineptr[], int left, int right,
                int (*comp)(void *, void *));
void quick_sort_field(void *lineptr[], int left, int right,
                      struct FieldSort fields[], int fieldsCount);

int numcmp(char *, char *);
int rnumcmp(char *, char *);
int rstrcmp(char *, char *);
int foldstrcmp(char *, char *);
int foldresversestrcmp(char *, char *);
int directoryycmp(char *, char *);
int reversedirectorycmp(char *, char *);
int folddirectorycmp(char *, char *);
int foldreversedirectorycmp(char *, char *);

int (*choose_sort_strategy(bool numeric, bool reverse, bool fold,
                           bool directory))(void *, void *) {
  if (numeric) {
    return reverse ? (int (*)(void *, void *))rnumcmp
                   : (int (*)(void *, void *))numcmp;
  } else if (reverse) {
    if (fold) {
      return directory ? (int (*)(void *, void *))foldreversedirectorycmp
                       : (int (*)(void *, void *))foldresversestrcmp;
    } else {
      return directory ? (int (*)(void *, void *))reversedirectorycmp
                       : (int (*)(void *, void *))rstrcmp;
    }
  } else if (fold) {
    return directory ? (int (*)(void *, void *))folddirectorycmp
                     : (int (*)(void *, void *))foldstrcmp;
  } else if (directory) {
    return (int (*)(void *, void *))directoryycmp;
  } else {
    return (int (*)(void *, void *))strcmp;
  }
}

/* sort input lines */
int main(int argc, char *argv[]) {
  int nlines;           /* number of input lines read */
  bool numeric = false; /* 1 if numeric sort */
  bool reverse = false;
  bool fold = false;
  bool directory = false;
  int fieldsCount = 0;

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
      case 'd': {
        directory = true;
        break;
      }
      case 'k': {
        struct FieldSort field = {.start = 0,
                                  .end = 0,
                                  .fold = false,
                                  .reverse = false,
                                  .directory = false,
                                  .numeric = false};
        if ((*++argv)[0] == '-') {
          argc--;
          int c;
          while (c = *++argv[0]) {
            switch (c) {
            case 'n': {
              field.numeric = true;
              break;
            }
            case 'r': {
              field.reverse = true;
              reverse = true;
              break;
            }
            case 'f': {
              field.fold = true;
              fold = true;
              break;
            }
            case 'd': {
              field.directory = true;
              directory = true;
              break;
            }
            default: {
              printf("Invalid argument: %s\n", *argv);
              break;
            }
            }
          }
        }
        argv++;
        char *startAndEnd = *argv;
        const char delimiter[] = ",";
        int start, end;

        if (startAndEnd != NULL && isdigit(startAndEnd[0])) {
          argc--;
          char *token = strtok(startAndEnd, delimiter);
          if (token != NULL && isdigit(token[0])) {
            start = atoi(token);
            field.start = start;
            token = strtok(startAndEnd, delimiter);
            if (token != NULL && isdigit(token[0])) {
              end = atoi(token);
              field.end = end;
            } else {
              printf("No end got %s\n", token);
            }
          } else {
            printf("No start got %s\n", token);
          }

        } else {
          printf("No start and end\n");
        }

        if (start > end) {
          printf("start is > end \n");
        }

        fields[fieldsCount] = field;
        fieldsCount++;
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
    if (fieldsCount == 0) {
      int (*cmp)(void *, void *) =
          choose_sort_strategy(numeric, reverse, fold, directory);
      quick_sort((void **)lineptr, 0, nlines - 1, cmp);
      writelines(lineptr, nlines);
      return 0;
    } else {
      quick_sort_field((void **)lineptr, 0, nlines - 1, fields, fieldsCount);
      writelines(lineptr, nlines);
      return 0;
    }

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

void quick_sort_field(void *v[], int left, int right, struct FieldSort fields[],
                      int fieldsCount) {
  int i, last;
  void swap(void *v[], int, int);
  if (left >= right) /* do nothing if array contains */
    return;          /* fewer than two elements */
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++) {
    int resultComp = 0;
    for (int count = 0; resultComp == 0 && count < fieldsCount; count++) {
      struct FieldSort field = fields[count];
      int (*comp)(void *, void *) = choose_sort_strategy(
          field.numeric, field.reverse, field.fold, field.directory);
      char *extractField1 = extractfields(v[i], field.start, field.end);
      char *extractField2 = extractfields(v[left], field.start, field.end);
      resultComp = (*comp)(extractField1, extractField2);
      if (resultComp < 0) {
        swap(v, ++last, i);
      }
      free(extractField1);
      free(extractField2);
    }
  }

  swap(v, left, last);
  quick_sort_field(v, left, last - 1, fields, fieldsCount);
  quick_sort_field(v, last + 1, right, fields, fieldsCount);
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

int directoryycmp(char *s1, char *s2) {
  char *directorys1 = directorystr(s1);
  char *directorys2 = directorystr(s2);
  int result = strcmp(directorys1, directorys2);
  free(directorys1);
  free(directorys2);
  return result;
}

int reversedirectorycmp(char *s1, char *s2) { return directoryycmp(s2, s1); }

int foldstrcmp(char *s1, char *s2) {
  char *lowereds1 = lowercase(s1);
  char *lowereds2 = lowercase(s2);
  int result = strcmp(lowereds1, lowereds2);
  free(lowereds1);
  free(lowereds2);
  return result;
}

int folddirectorycmp(char *s1, char *s2) {
  char *directorys1 = directorystr(s1);
  char *directorys2 = directorystr(s2);
  int result = foldstrcmp(directorys1, directorys2);
  free(directorys1);
  free(directorys2);
  return result;
}

int foldreversedirectorycmp(char *s1, char *s2) {
  return folddirectorycmp(s2, s1);
}

int foldresversestrcmp(char *s1, char *s2) { return foldstrcmp(s2, s1); }

void swap(void *v[], int i, int j) {
  void *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
