#include <_ctype.h>
#include <ctype.h>
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
        char *char_p = va_arg(ap, char *);
        *char_p++ = c;
        for (int i = 0; !isspace(c = getchar()); i++) {
          if (has_width && width == i) {
            ungetch(c);
            break;
          }
          *char_p++ = c;
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
  int num;
  int num2;
  char s[100];
  minscanf("%d %s %d", &num, &s, &num2);
  printf("%d %s %d\n", num, s, num2);
  return 0;
}
