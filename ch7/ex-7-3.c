#include "../ch6/take-first.c"
#include <_ctype.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_padded_str(char *str, bool has_first_int, int first_int) {
  int str_len = strlen(str);
  if (has_first_int && first_int > 0) {
    int pad_start_len = first_int - str_len;
    for (int i = 0; i < pad_start_len; i++) {
      putchar(' ');
    }
  }
  for (; *str; str++) {
    putchar(*str);
  }
  if (has_first_int && first_int < 0) {
    int pad_start_len = abs(first_int) - str_len;
    for (int i = 0; i < pad_start_len; i++) {
      putchar(' ');
    }
  }
}

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
      if (isnumber(*p)) {
        second_int = 10 * second_int + (*p++ - '0');
        for (; isnumber(*p); p++) {
          second_int = 10 * second_int + (*p - '0');
        }
        has_second_int = true;
      } else if (*p == '*') {
        second_int = va_arg(ap, int);
        second_int = true;
        p++;
      }
    }

    char str[sizeof(long)];
    switch (*p) {
    case 'd':
    case 'i':
      ival = va_arg(ap, int);
      sprintf(str, "%d", ival);
      display_padded_str(str, has_first_int, first_int);
      break;
    case 'f':
      dval = va_arg(ap, double);
      printf("%f", dval);
      break;
    case 'e':
      dval = va_arg(ap, double);
      printf("%e", dval);
      break;
    case 'G':
    case 'g':
      dval = va_arg(ap, double);
      printf("%g", dval);
      break;
    case 'c':
      ival = va_arg(ap, int);
      sprintf(str, "%c", ival);
      display_padded_str(str, has_first_int, first_int);
      break;
    case 'u':
      ival = va_arg(ap, int);
      sprintf(str, "%u", ival);
      display_padded_str(str, has_first_int, first_int);
      break;
    case 'o':
      ival = va_arg(ap, int);
      sprintf(str, "%o", ival);
      display_padded_str(str, has_first_int, first_int);
      break;
    case 'x':
    case 'X':
      ival = va_arg(ap, int);
      sprintf(str, "%x", ival);
      display_padded_str(str, has_first_int, first_int);
      break;
    case 's':
      sval = va_arg(ap, char *);
      if (has_second_int) {
        char *final_s;
        final_s = take_first(sval, second_int);
        display_padded_str(final_s, has_first_int, first_int);
        free(final_s);
      } else {
        display_padded_str(sval, has_first_int, first_int);
      }
      break;
    case 'p':
      void_p = va_arg(ap, void *);
      sprintf(str, "%p", void_p);
      display_padded_str(str, has_first_int, first_int);
      break;
    default:
      putchar(*p);
      break;
    }
  }
  va_end(ap); /* clean up when done */
}

int main() { minprintf("%x %x %x %x %x\n", 255, 255, 255, 255, 255); }
