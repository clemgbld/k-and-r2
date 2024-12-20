#include <_ctype.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>

#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */
int getch(void)    /* get a (possibly pushed-back) character */
{
  if (bufp > 0)
    return buf[--bufp];
  int c = getchar();
  return c;
}
void ungetch(int c) /* push character back on input */
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

#define parse_number(c, number, has_width, width)                              \
  {                                                                            \
    number = 0;                                                                \
    number = 10 * number + (c - '0');                                          \
    width--;                                                                   \
    for (; isnumber(c = getch());) {                                           \
      if (width == 0) {                                                        \
        ungetch(c);                                                            \
        break;                                                                 \
      }                                                                        \
      number = 10 * number + (c - '0');                                        \
      width--;                                                                 \
    }                                                                          \
  }

#define parse_decimal(c, dval, has_width, width, sign)                         \
  {                                                                            \
    if (c == '.') {                                                            \
      width--;                                                                 \
      if (width > 1 || !has_width) {                                           \
        int power = 1;                                                         \
        for (; isdigit(c = getch());) {                                        \
          if (has_width && width == 0) {                                       \
            break;                                                             \
          }                                                                    \
          dval = (10.0 * dval) + (c - '0');                                    \
          power *= 10;                                                         \
          width--;                                                             \
        }                                                                      \
        dval = dval / power;                                                   \
        if (width > 1 || !has_width) {                                         \
          if (c == 'e' || c == 'E') {                                          \
            c = getch();                                                       \
            width--;                                                           \
            if (width > 1 || !has_width) {                                     \
              if (c == '-') {                                                  \
                sign = -1;                                                     \
                width--;                                                       \
              } else if (c == '+') {                                           \
                sign = 1;                                                      \
                width--;                                                       \
              }                                                                \
              if (width > 1 || !has_width) {                                   \
                double exp = 0;                                                \
                for (; isdigit(c = getch());) {                                \
                  if (has_width && width == 0) {                               \
                    break;                                                     \
                  }                                                            \
                  exp = (10 * exp) + (c - '0');                                \
                  width--;                                                     \
                }                                                              \
                if (exp > 0) {                                                 \
                  dval = (dval) * (pow(10, (sign * exp)));                     \
                }                                                              \
              }                                                                \
            }                                                                  \
          }                                                                    \
        }                                                                      \
      }                                                                        \
    }                                                                          \
  }

int minscanf(char *fmt, ...) {
  va_list ap;        /* points to each unnamed arg in turn */
  va_start(ap, fmt); /* make ap point to 1st unnamed arg */
  int n = 0;
  char str[100];

  for (; *fmt; fmt++) {
    int c;

    while (isspace(*fmt)) {
      fmt++;
    }

    if (*fmt == '%') {
      fmt++;
      int width = 0;
      int has_width = 0;
      int should_skip = 0;
      int has_l_modifier = 0;
      int has_L_modifier = 0;
      int has_h_modifier = 0;
      int is_negative = 0;

      if (*fmt != 'c') {
        while (isspace(c = getch()))
          ;
      } else {
        c = getch();
      }

      if (isnumber(*fmt)) {
        width = 10 * width + (*fmt++ - '0');
        for (; isnumber(*fmt); fmt++) {
          width = 10 * width + (*fmt - '0');
        }
        has_width = 1;
      } else if (*fmt == '*') {
        fmt++;
        should_skip = 1;
      }

      if (*fmt == 'l') {
        fmt++;
        has_l_modifier = 1;
      } else if (*fmt == 'h') {
        fmt++;
        has_h_modifier = 1;
      } else if (*fmt == 'L') {
        fmt++;
        has_L_modifier = 1;
      }

      if (*fmt == 'd' || *fmt == 'i') {

        if (c == '-') {
          is_negative = 1;
          c = getch();
        }

        if (!isnumber(c)) {
          break;
        }
        if (has_h_modifier) {
          short sval;
          parse_number(c, sval, has_width, width);
          if (!should_skip) {
            short *short_p = va_arg(ap, short *);
            *short_p = is_negative ? sval * -1 : sval;
          }
        } else if (has_l_modifier) {
          long lval;
          parse_number(c, lval, has_width, width);
          if (!should_skip) {
            long *long_p = va_arg(ap, long *);
            *long_p = is_negative ? lval * -1 : lval;
          }
        } else {
          int ival;
          parse_number(c, ival, has_width, width);
          if (!should_skip) {
            int *int_p = va_arg(ap, int *);
            *int_p = is_negative ? ival * -1 : ival;
          }
        }
        ungetch(c);
        continue;
      }

      if (*fmt == 'c') {
        if (!should_skip) {
          char *char_p = va_arg(ap, char *);
          *char_p = c;
        }
        continue;
      }

      if (*fmt == 's') {
        if (should_skip) {
          for (int i = 0; !isspace(c = getchar()); i++) {
            if (has_width && width == i) {
              break;
            }
          }
        } else {
          char *char_p = va_arg(ap, char *);
          *char_p++ = c;
          for (int i = 0; !isspace(c = getchar()); i++) {
            if (has_width && width == i) {
              break;
            }
            *char_p++ = c;
          }
        }
        ungetch(c);
        continue;
      }

      if (*fmt == 'e' || *fmt == 'f' || *fmt == 'g') {
        if (c == '-') {
          is_negative = 1;
          c = getch();
        }

        if (!isnumber(c)) {
          break;
        }
        int sign = is_negative ? -1 : 1;

        if (has_L_modifier) {
          long double ldval;
          parse_number(c, ldval, has_width, width);
          parse_decimal(c, ldval, has_width, width, sign);
          if (!should_skip) {
            long double *ld_p = va_arg(ap, long double *);
            *ld_p = is_negative ? ldval * -1 : ldval;
          }
        } else if (has_l_modifier) {
          double dval;
          parse_number(c, dval, has_width, width);
          parse_decimal(c, dval, has_width, width, sign);
          if (!should_skip) {
            double *d_p = va_arg(ap, double *);
            *d_p = is_negative ? dval * -1 : dval;
          }
        } else {
          float fval;
          parse_number(c, fval, has_width, width);
          parse_decimal(c, fval, has_width, width, sign);
          if (!should_skip) {
            float *f_p = va_arg(ap, float *);
            *f_p = is_negative ? fval * -1 : fval;
          }
        }

        ungetch(c);
        continue;
      }

    } else {
      while (isspace(c = getch()))
        ;

      if (c != *fmt) {
        break;
      }
    }
  }

  va_end(ap); /* clean up when done */
  return n;
}

int main() {
  double dval;
  minscanf("%lf", &dval);
  printf("%f\n", dval);
  return 0;
}
