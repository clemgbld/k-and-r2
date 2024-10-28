#include <string.h>

void reverseRecur(char s[], int i, int j) {
  if (i < j) {
    int c = s[i];
    s[i] = s[j];
    s[j] = c;
    reverseRecur(s, i + 1, j - 1);
  }
}

void reverse(char s[]) { reverseRecur(s, 0, strlen(s) - 1); }
