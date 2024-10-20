#include <stdlib.h>
#include <string.h>

char *reverse(char *str) {

  int length = strlen(str);

  char *reversed = malloc(length + 1);

  int i = length - 1;
  int j = 0;

  while (i != -1) {
    reversed[j] = str[i];
    i--;
    j++;
  }

  reversed[j] = '\0';

  return reversed;
}

int strrindex(char s[], char t[]) {
  char *pattern = reverse(t);
  for (int i = strlen(s); i >= 0; i--) {

    int j, k;

    for (j = i, k = 0; pattern[k] != '\0' && s[j] == pattern[k]; k++, j--)
      ;

    if (k > 0 && pattern[k] == '\0') {
      return i;
    }
  }
  free(pattern);
  return -1;
}
