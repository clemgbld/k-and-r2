#include <stdio.h>

int main() {

  int assci[128] = {0};
  int c;

  while ((c = getchar()) != EOF) {
    assci[c] = assci[c] + 1;
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
