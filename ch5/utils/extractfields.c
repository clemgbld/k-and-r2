#include "extractfields.h"
#include <stdlib.h>
#include <string.h>

char *extractfields(char *str, int start, int end) {
  char *result = malloc(strlen(str) + 1);
  char *begin = result;

  while (start > 1) {
    while (*str != ' ' && *str != '\0') {
      str++;
    }
    if (*str != '\0') {
      str++;
    }
    start--;
  }

  int count = 0;

  while (*str != '\0') {
    if (*str == ' ' && end == ++count) {
      break;
    }
    *result++ = *str++;
  }

  *result = '\0';
  return begin;
}
