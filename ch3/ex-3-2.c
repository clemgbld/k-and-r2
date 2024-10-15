void escape(char s[], char t[]) {
  int j = 0;
  for (int i = 0; s[i] != '\0'; i++) {
    int c = s[i];
    switch (c) {
    case '\n': {
      t[j] = '\\';
      t[j + 1] = 'n';
      j++;
      break;
    }
    case '\t': {
      t[j] = '\\';
      t[j + 1] = 't';
      j++;
      break;
    }
    default: {
      t[j] = c;
      break;
    }
    }

    j++;
  }
  t[j] = '\0';
}

void escapeReverse(char s[], char t[]) {
  int j = 0;
  for (int i = 0; s[i] != '\0'; i++) {
    int c = s[i];
    if (c == '\\') {
      switch (s[i + 1]) {
      case 'n': {
        t[j] = '\n';
        i++;
        break;
      }
      case 't': {
        t[j] = '\t';
        i++;
        break;
      }
      }

    } else {
      t[j] = c;
    }
    j++;
  }
  t[j] = '\0';
}
