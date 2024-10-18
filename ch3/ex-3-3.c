
int isInRange(char c) {
  return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9';
}

int isWrongRange(char start, char end) {
  return start >= end || start <= 'Z' && end > 'Z' || start <= '9' && end > '9';
}

void expand(char s1[], char s2[]) {
  int i = 0;
  int j = 0;
  if (s1[i] == '\0') {

    s2[j] = '\0';
    return;
  }

  for (; !isInRange(s1[i]); i++, j++) {
    s2[j] = s1[i];
  }

  char start = 0;
  char separator = 0;

  for (; s1[i] != '\0'; i++) {

    if (start != 0 && separator == 0 && !isInRange(s1[i])) {
      separator = s1[i];
      continue;
    }

    if (start != 0 && separator != 0 && !isInRange(s1[i])) {
      s2[j] = separator;
      j++;
      start = 0;
      separator = 0;
      for (; !isInRange(s1[i]); i++, j++) {
        s2[j] = s1[i];
      }
      i--;
      continue;
    }

    if (isInRange(s1[i])) {
      if (start == 0) {
        start = s1[i];
        s2[j] = s1[i];
        j++;
      } else if (start != 0 && separator == '-') {
        if (isWrongRange(start, s1[i])) {
          s2[j] = separator;
          j++;
          s2[j] = s1[i];
          j++;
        } else {
          for (char k = start + 1; k <= s1[i]; k++, j++)
            s2[j] = k;
        };

        start = s1[i];
        separator = 0;
      } else if (start != 0 && separator == 0) {
        start = s1[i];
        s2[j] = s1[i];
        j++;
      } else {
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
