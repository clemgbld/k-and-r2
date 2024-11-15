#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *directorystr(char *str) {
  char *result = malloc(strlen(str) + 1);
  char *begin = result;

  while (*str != '\0') {
    if (isalnum(*str)) {
      *result++ = *str++;
    } else {
      str++;
    }
  }

  *result = '\0';

  return begin;
};
