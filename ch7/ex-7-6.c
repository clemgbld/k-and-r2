#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1000

int main(int argc, char *argv[]) {

  if (argc < 3) {
    fprintf(stderr, "%s : please provide two file names", argv[0]);
    exit(1);
  }

  FILE *fp1 = fopen(argv[1], "r");
  if (fp1 == NULL) {
    fprintf(stderr, "%s : can open this file %s", argv[0], argv[1]);
    exit(2);
  }

  FILE *fp2 = fopen(argv[2], "r");
  if (fp2 == NULL) {
    fprintf(stderr, "%s : can open this file %s", argv[0], argv[2]);
    exit(2);
  }

  char line1[MAX_LINE];
  char line2[MAX_LINE];
  char *l1p = NULL;
  char *l2p = NULL;
  int count = 1;

  while ((l1p = fgets(line1, MAX_LINE, fp1)) != NULL &&
         (l2p = fgets(line2, MAX_LINE, fp2)) != NULL) {
    if (strcmp(line1, line2) != 0) {
      printf("Differ at line %d\n", count);
      printf("line of file 1 that differ: %s", line1);
      printf("line of file 2 that differ: %s", line2);
      break;
    }
    count++;
  }

  if (l1p == NULL && l2p != NULL) {
    printf("Differ at line %d\n", count);
    printf("line of file 2 that differ: %s", line2);
    printf("end of file 1 at line: %d", count - 1);
  } else if (l2p == NULL && l1p != NULL) {
    printf("Differ at line %d\n", count);
    printf("line of file 1 that differ: %s", line1);
    printf("end of file 2 at line: %d", count - 1);
  }

  fclose(fp1);
  fclose(fp2);

  exit(0);
}
