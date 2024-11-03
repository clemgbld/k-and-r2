#include <sys/signal.h>
void strncat_custom(char *s, char *t, size_t n) {
  for (; *s != '\0'; *s++)
    ;
  while (*t != '\0') {
    if (n == 0) {
      *s = '\0';
      return;
    }
    *s++ = *t++;
    n--;
  }
}

void strncpy_custom(char *s, char *t, size_t n) {
  while (*s++ = *t++) {
    n--;
    if (n == 0) {
      *s = '\0';
      return;
    }
  }
}

int strncmp_custom(char *s, char *t, size_t n) {
  for (; *s == *t; *s++, t++) {
    n--;
    if (*s == '\0' || n == 0)
      return 0;
  }

  return *s - *t;
}
