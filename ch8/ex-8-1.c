#include "unistd.h"
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/* error: print an error message and die */
void error(char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  fprintf(stderr, "error: ");
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
  va_end(args);
  exit(1);
}

int main(int argc, char *argv[]) {
  char buf[BUFSIZ];
  int fd;
  while (--argc > 0) {
    char *filename = *++argv;
    fd = open(filename, O_RDONLY, 0);
    if (fd == -1) {
      error("cp: can't open %s", filename);
    }
    int n;
    while ((n = read(fd, buf, BUFSIZ)) > 0) {
      if (write(1, buf, n)) {
        error("can't write to stdout");
      }
    }
    close(fd);
  }
  return 0;
}
