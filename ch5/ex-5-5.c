void strncat_custom(char *s, char *t, int n) {
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

void strncpy_custom(char *s, char *t, int n) { *s = *t; }
