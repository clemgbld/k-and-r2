#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 1000
#define MAX_LINE_PAGE 30

int main(int argc, char *argv[]) {
  int page_count = 0;
  char line[MAX_LINE];
  int lineno = 0;
  while (--argc > 0) {
    char *filename = *++argv;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
      printf("can't open file %s\n", filename);
      exit(1);
    }
    page_count++;
    printf("TITLE: %s - PAGE: %d\n", filename, page_count);
    while (fgets(line, MAX_LINE, fp) != NULL) {
      if (lineno == MAX_LINE_PAGE) {
        printf("PAGE: %d\n", page_count);
        page_count++;
        lineno = 0;
      }
      printf("%s", line);
      lineno++;
    }

    if (ferror(fp)) {
      printf("error while reading file : %s", filename);
      exit(2);
    }
    fclose(fp);
  }
  exit(0);
}
