#include <stdio.h>

int main() {
  float celsius;
  float lower = 0;
  float upper = 300;
  float step = 20;
  float fahr = lower;

  printf("Fahrenheit -> Celsius Table:\n");
  while (fahr <= upper) {
    celsius = (5.0 / 9.0) * (fahr - 32.0);
    printf("%3.0f %6.1f\n", fahr, celsius);
    fahr = fahr + step;
  }
}
