#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {

  int c;

  if (strcmp(argv[0], "lower") == 0) {
    while ((c = getchar()) != EOF) {
      putchar(tolower(c));
    }
  } else if (strcmp(argv[0], "upper") == 0) {
    while ((c = getchar()) != EOF) {
      putchar(toupper(c));
    }
  } else {
    printf("the name of this program must be either lower or upper\n");
    return 1;
  }

  return 0;
}
