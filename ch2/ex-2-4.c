#include <string.h>

int includes(int c, char str[]) {
  for (int i = 0; i < strlen(str); i++) {
    if (c == str[i])
      return 1;
  }
  return 0;
}

void squeeze(char str1[], char str2[]) {
  int i, j;
  for (i = j = 0; str1[i] != '\0'; i++)
    if (!includes(str1[i], str2))
      str1[j++] = str1[i];
  str1[j] = '\0';
}
