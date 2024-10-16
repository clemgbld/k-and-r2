
int isInRange(char c) {
  return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9';
}

void expand(char s1[], char s2[]) {
  int i = 0;
  int j = 0;

  for (; !isInRange(s1[i]); i++, j++) {
    s2[j] = s1[i];
  }

  char start = 0;
  char separator = 0;

  for (; s1[i] != '\0'; i++) {
    if (start != 0 && separator == 0) {
      separator = s1[i];
      continue;
    }
    if (isInRange(s1[i])) {
      if (start == 0) {
        start = s1[i];
      } else if (start != 0 && separator == '-') {
        for (char k = start; k <= s1[i]; k++, j++)
          s2[j] = k;
        start = 0;
        separator = 0;
      } else {
        s2[j] = start;
        j++;
        s2[j] = separator;
        j++;
        s2[j] = s1[i];
        j++;
        start = 0;
        separator = 0;
      }
    }
  }

  s2[j] = '\0';
}
