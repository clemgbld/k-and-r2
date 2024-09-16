#include <stdio.h>

float fahrToCelsius(float fahr) { return (5.0 / 9.0) * (fahr - 32.0); }

int main() {

  float lower = 0;
  float upper = 300;
  float step = 20;
  float fahr = lower;
  float celsius;

  while (fahr <= upper) {
    printf("%3.0f %6.1f\n", fahr, fahrToCelsius(fahr));
    fahr = fahr + step;
  }

  return 0;
}
