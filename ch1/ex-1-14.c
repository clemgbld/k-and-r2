#include <stdio.h>

int main() {

  int assci[52] = {0};
  int c;

  while ((c = getchar()) != EOF) {
    if (c >= 'a' && c <= 'z') {
      assci[c - 'a'] = assci[c - 'a'] + 1;
    } else if (c >= 'A' && c <= '2') {
      assci[c - 'A'] = assci[c - 'A'] + 1;
    }
  }

  for (int i = 0; i < 127; i++) {
    printf("%d", i);
    int count = assci[i];
    for (int j = 0; j < count; j++) {
      printf("-");
    }
    printf("\n");
  }

  return 0;
}
