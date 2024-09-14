#include <stdio.h>

int main() {
  float fahr;
  float lower = 0;
  float upper = 300;
  float step = 20;
  float celsius = lower;

  printf("Celsius -> Farenheit Table:\n");
  while (fahr <= upper) {
    fahr = (celsius * (9.0 / 5.0)) + 32.0;
    printf("%3.0f %6.1f\n", celsius, fahr);
    celsius = celsius + step;
  }
}
