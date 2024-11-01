void strcat_custom(char *s, char *t) {
  for (; *s != '\0'; *s++)
    ;
  while (*t != '\0') {
    *s++ = *t++;
  }
}
