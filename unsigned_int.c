#include <stdarg.h>
#include <stdio.h>
#include "main.h"

int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    char c;

    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++;  // skip '%'

            switch (*format) {
                case 'c':
                    c = (char) va_arg(args, int);
                    putchar(c);
                    count++;
                    break;

                case 's':
                    const char *s = va_arg(args, const char *);
                    while (*s != '\0') {
                        putchar(*s);
                        s++;
                        count++;
                    }
                    break;

                case 'd':
                    // handle decimal integer
                    int d = va_arg(args, int);
                    printf("%d", d);
                    count++;
                    break;

                case 'b':
                    // handle binary integer
                    unsigned int b = va_arg(args, unsigned int);
                    int bits = sizeof(b) * 8;  // number of bits in unsigned int
                    int mask = 1 << (bits - 1);  // start with most significant bit
                    for (int i = 0; i < bits; i++) {
                        putchar(b & mask ? '1' : '0');
                        mask >>= 1;  // shift mask to next bit
                        count++;
                    }
                    break;

                case '%':
                    putchar('%');
                    count++;
                    break;

                default:
                    // unsupported conversion specifier, ignore it
                    break;
            }

        } else {
            putchar(*format);
            count++;
        }

        format++;
    }

    va_end(args);

    return count;
}
