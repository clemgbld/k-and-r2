#include <string.h>

int strend(char *s, char *t) {
  const int BEGIN = 0;
  s += strlen(s) - 1;
  t += strlen(t) - 1;

  while (*t != BEGIN) {
    if (*s != *t) {
      return 0;
    }
    s--;
    t--;
  }

  return 1;
}
