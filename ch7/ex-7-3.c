#include <_ctype.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...) {
  va_list ap; /* points to each unnamed arg in turn */
  char *p, *sval;
  void *void_p;
  int ival;
  double dval;
  va_start(ap, fmt); /* make ap point to 1st unnamed arg */
  for (p = fmt; *p; p++) {
    if (*p != '%') {
      putchar(*p);
      continue;
    }

    int first_int = 0;
    int second_int = 0;
    int has_first_int = false;
    int has_second_int = false;
    int is_negative = false;

    if (*++p == '-') {
      is_negative = true;
      p++;
    }

    if (isnumber(*p)) {
      first_int = 10 * first_int + (*p++ - '0');
      for (; isnumber(*p); p++) {
        first_int = 10 * first_int + (*p - '0');
      }
      if (is_negative) {
        first_int = first_int * -1;
        is_negative = false;
      }
      has_first_int = true;
    } else if (*p == '*') {
      first_int = va_arg(ap, int);
      if (is_negative) {
        first_int = first_int * -1;
        is_negative = false;
      }
      has_first_int = true;
      p++;
    }

    if (*p == '.') {
      p++;
    }

    switch (*p) {
    case 'd':
      ival = va_arg(ap, int);
      printf("%d", ival);
      break;
    case 'i':
      ival = va_arg(ap, int);
      printf("%d", ival);
      break;
    case 'f':
      dval = va_arg(ap, double);
      printf("%f", dval);
      break;
    case 'e':
      dval = va_arg(ap, double);
      printf("%e.ddd", dval);
      break;
    case 'g':
      dval = va_arg(ap, double);
      printf("%g", dval);
      break;
    case 'c':
      ival = va_arg(ap, int);
      printf("%c", ival);
      break;
    case 'u':
      ival = va_arg(ap, int);
      printf("%u", ival);
      break;
    case 'o':
      ival = va_arg(ap, int);
      printf("%o", ival);
      break;
    case 'x':
      ival = va_arg(ap, int);
      printf("%x", ival);
      break;
    case 's':
      for (sval = va_arg(ap, char *); *sval; sval++)
        putchar(*sval);
      break;
    case 'p':
      void_p = va_arg(ap, void *);
      printf("%p", void_p);
      break;
    default:
      putchar(*p);
      break;
    }
  }
  va_end(ap); /* clean up when done */
}

int main() { return 0; }
