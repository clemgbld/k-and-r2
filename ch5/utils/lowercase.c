#include "lowercase.h"
#include <stdlib.h>
#include <string.h>

char *lowercase(char str[]) {
  char *lowered = malloc(strlen(str) + 1);
  char *begin = lowered;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      *lowered++ = str[i] + 32;
    } else {
      *lowered++ = str[i];
    }
  }

  *lowered = '\0';
  return begin;
}
