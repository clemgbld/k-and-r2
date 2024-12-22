#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  if (argc < 3) {
    fprintf(stderr, "%s : please provide two file names", argv[0]);
    exit(1);
  }

  exit(0);
}
