#include <stdio.h>

int main() {
  int c;
  int counter = 0;
  int histo[45] = {0};
  while ((c = getchar()) != EOF) {
    if (!(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z')) {
      histo[counter] = histo[counter] + 1;
      counter = 0;
    } else {
      counter++;
    }
  }

  for (int i = 0; i < 45; i++) {
    int count = histo[i];
    if (count > 0) {
      printf("%d ", i);
    }
    for (int j = 0; j < count; j++) {
      printf("-");
      if ((j + 1) == count) {
        printf("\n");
      }
    }
  }
}
