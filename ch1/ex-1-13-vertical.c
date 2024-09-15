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
    } else {
      histo[i] = -1;
    }
  }
  printf("\n");

  int greater = 0;

  while (1) {
    for (int i = 0; i < 45; i++) {
      int count = histo[i];
      if (count > greater) {
        greater = count;
      }
    }

    if (greater == 0) {
      break;
    }

    for (int i = 0; i < 45; i++) {
      int count = histo[i];
      if (count == greater) {
        histo[i] = histo[i] - 1;
        if (i > 8) {
          printf("|  ");
        } else {
          printf("| ");
        }
      } else if (count > -1) {
        if (i > 8) {
          printf("   ");
        } else {
          printf("  ");
        }
      }
    }
    printf("\n");
    greater = 0;
  }
}
