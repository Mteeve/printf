#include <stdarg.h>
#include <stdio.h>
#include "main.h"

int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;

    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++;  // skip '%'

            switch (*format) {
                case 'c':
                    putchar(va_arg(args, int));
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

                case '%':
                    putchar('%');
                    count++;
                    break;

                case 'd':
                    printf("%d", va_arg(args, int));
                    count++;
                    break;

                case 'u':
                    printf("%u", va_arg(args, unsigned int));
                    count++;
                    break;

                case 'o':
                    printf("%o", va_arg(args, unsigned int));
                    count++;
                    break;

                case 'x':
                    printf("%x", va_arg(args, unsigned int));
                    count++;
                    break;

                case 'X':
                    printf("%X", va_arg(args, unsigned int));
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
