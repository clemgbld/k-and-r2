#include <stdlib.h>

char *take_first(char *str, int slice) {
  char *result = malloc(slice + 1);
  char *start = result;
  while (*str != '\0' && slice != 0) {
    *result++ = *str++;
    slice--;
  }

  *result = '\0';
  return start;
}
