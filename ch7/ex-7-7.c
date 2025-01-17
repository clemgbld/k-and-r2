#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

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

/* find: print lines that match pattern from 1st arg */
int main(int argc, char *argv[]) {
  char line[MAXLINE];
  long lineno = 0;
  int c, except = 0, number = 0, found = 0;

  while (--argc > 0 && (*++argv)[0] == '-') {
    while ((c = *++argv[0]))
      switch (c) {
      case 'x':
        except = 1;
        break;
      case 'n':
        number = 1;
        break;
      default:
        printf("find: illegal option %c\n", c);
        argc = 0;
        found = -1;
        break;
      }
  }

  if (argc < 1) {
    printf("Usage: find -x  -n pattern [file1] [file2]... \n");
    return 1;
  }
  if (argc == 1) {
    while (getLine(line, MAXLINE) > 0) {
      lineno++;
      if ((strstr(line, *argv) != NULL) != except) {
        if (number)
          printf("%ld:", lineno);
        printf("%s", line);
        found++;
      }
    }
  } else {
    char *pattern = *argv;
    while (--argc > 0) {
      char *filename = *++argv;
      FILE *fp = fopen(filename, "r");
      if (fp == NULL) {
        fprintf(stderr, "%s : can open this file %s", argv[0], filename);
        return 1;
      }
      while (fgets(line, MAXLINE, fp) != NULL) {
        lineno++;
        if ((strstr(line, pattern) != NULL) != except) {
          if (number)
            printf("%ld:", lineno);
          printf("filename: %s\n%s\n", filename, line);
          found++;
        }
      }
      if (ferror(fp))
        fprintf(stderr, "%s: file error\n", filename);
      fclose(fp);
      lineno = 0;
    }
  }

  return found;
}
