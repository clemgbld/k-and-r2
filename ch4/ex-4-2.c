#include <ctype.h>
#include <math.h>
#include <string.h>

double atofcustom(char s[]) {
  double val, power, exp;
  int i, sign;
  for (i = 0; isspace(s[i]); i++)
    ;
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
    i++;
  for (val = 0.0; isdigit(s[i]); i++)
    val = 10.0 * val + (s[i] - '0');
  if (s[i] == '.')
    i++;
  for (power = 1.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10;
  }

  double result = sign * val / power;

  if (s[i] == 'e' || s[i] == 'E') {
    i++;
  }

  if (s[i] == '-') {
    sign = -1;
    i++;
  } else {
    if (s[i] == '+')
      i++;
    sign = 1;
  }

  if (isdigit(s[i])) {
    char expStr[(strlen(s) + 1) - i];
    for (int j = 0; isdigit(s[i]); i++, j++) {
      expStr[j] = s[i];
    }
    result = result * pow(10, sign * atofcustom(expStr));
  }

  return result;
}
