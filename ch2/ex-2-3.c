#include <ctype.h>
#include <math.h>
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

int htoi(char str[]) {

  char *reversedStr = reverse(str);

  int n = 0;

  for (int i = 0; isdigit(reversedStr[i]) ||
                  reversedStr[i] >= 'a' && reversedStr[i] <= 'f' ||
                  reversedStr[i] >= 'A' && reversedStr[i] <= 'F';
       i++) {
    if (isdigit(reversedStr[i])) {
      n += pow(16, i) * (reversedStr[i] - '0');
    }

    if (reversedStr[i] >= 'a' && reversedStr[i] <= 'f') {
      n += pow(16, i) * (reversedStr[i] - 'a' + 10);
    }

    if (reversedStr[i] >= 'A' && reversedStr[i] <= 'F') {
      n += pow(16, i) * (reversedStr[i] - 'A' + 10);
    }
  }

  free(reversedStr);

  return n;
}
