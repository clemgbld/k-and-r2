int includes(int c, char str[]) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (c == str[i])
      return 1;
  }
  return 0;
}

int any(char str1[], char str2[]) {
  for (int i = 0; str1[i] != '\0'; i++) {
    if (includes(str1[i], str2))
      return i;
  }
  return -1;
}
