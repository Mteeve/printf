#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include "main.h"

int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    char buffer[1024];
    int buffer_index = 0;

    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++;  // skip '%'

            switch (*format) {
                case 'c':
                    buffer[buffer_index++] = va_arg(args, int);
                    count++;
                    break;

                case 's': {
                    const char *s = va_arg(args, const char *);
                    while (*s != '\0') {
                        buffer[buffer_index++] = *s;
                        count++;
                        if (buffer_index == 1024) {
                            write(1, buffer, buffer_index);
                            buffer_index = 0;
                        }
                        s++;
                    }
                    break;
                }

                case 'p': {
                    void *ptr = va_arg(args, void *);
                    int chars_written = snprintf(buffer + buffer_index, 1024 - buffer_index, "%p", ptr);
                    buffer_index += chars_written;
                    count += chars_written;
                    break;
                }

                case '%':
                    buffer[buffer_index++] = '%';
                    count++;
                    break;

                case 'd':
                case 'i': {
                    int value = va_arg(args, int);
                    int chars_written = snprintf(buffer + buffer_index, 1024 - buffer_index, "%d", value);
                    buffer_index += chars_written;
                    count += chars_written;
                    break;
                }

                case 'u': {
                    unsigned int value = va_arg(args, unsigned int);
                    int chars_written = snprintf(buffer + buffer_index, 1024 - buffer_index, "%u", value);
                    buffer_index += chars_written;
                    count += chars_written;
                    break;
                }

                case 'o': {
                    unsigned int value = va_arg(args, unsigned int);
                    int chars_written = snprintf(buffer + buffer_index, 1024 - buffer_index, "%o", value);
                    buffer_index += chars_written;
                    count += chars_written;
                    break;
                }

                case 'x': {
                    unsigned int value = va_arg(args, unsigned int);
                    int chars_written = snprintf(buffer + buffer_index, 1024 - buffer_index, "%x", value);
                    buffer_index += chars_written;
                    count += chars_written;
                    break;
                }

                case 'X': {
                    unsigned int value = va_arg(args, unsigned int);
                    int chars_written = snprintf(buffer + buffer_index, 1024 - buffer_index, "%X", value);
                    buffer_index += chars_written;
                    count += chars_written;
                    break;
                }

                default:
                    break;
            }
        } else {
            buffer[buffer_index++] = *format;
            count++;
        }

        if (buffer_index == 1024) {
            write(1, buffer, buffer_index);
            buffer_index = 0;
        }

        format++;
    }

    if (buffer_index > 0) {
        write(1, buffer, buffer_index);
    }

    va_end(args);

    return count;
}
