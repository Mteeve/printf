#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include "main.h"

int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    char buffer[1024];
    int buffer_index = 0;
    int flag_plus = 0;
    int flag_space = 0;
    int flag_hash = 0;
    int length_modifier = 0;

    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++;  // skip '%'

            // Handle flags
            flag_plus = 0;
            flag_space = 0;
            flag_hash = 0;
            while (1) {
                if (*format == '+') {
                    flag_plus = 1;
                } else if (*format == ' ') {
                    flag_space = 1;
                } else if (*format == '#') {
                    flag_hash = 1;
                } else {
                    break;
                }
                format++;
            }

            // Handle length modifiers
            if (*format == 'l') {
                length_modifier = 1;
                format++;
            } else if (*format == 'h') {
                length_modifier = -1;
                format++;
            } else {
                length_modifier = 0;
            }

            // Handle conversion specifier
            if (*format == 'd' || *format == 'i') {
                int value;
                if (length_modifier == 1) {
                    value = va_arg(args, long);
                } else if (length_modifier == -1) {
                    value = (short)va_arg(args, int);
                } else {
                    value = va_arg(args, int);
                }
                buffer_index += sprintf(&buffer[buffer_index], "%+d", value);
            } else if (*format == 'u') {
                unsigned int value;
                if (length_modifier == 1) {
                    value = va_arg(args, unsigned long);
                } else if (length_modifier == -1) {
                    value = (unsigned short)va_arg(args, unsigned int);
                } else {
                    value = va_arg(args, unsigned int);
                }
                buffer_index += sprintf(&buffer[buffer_index], "%u", value);
            } else if (*format == 'o') {
                unsigned int value;
                if (length_modifier == 1) {
                    value = va_arg(args, unsigned long);
                } else if (length_modifier == -1) {
                    value = (unsigned short)va_arg(args, unsigned int);
                } else {
                    value = va_arg(args, unsigned int);
                }
                if (flag_hash) {
                    buffer_index += sprintf(&buffer[buffer_index], "0%o", value);
                } else {
                    buffer_index += sprintf(&buffer[buffer_index], "%o", value);
                }
            } else if (*format == 'x' || *format == 'X') {
                unsigned int value;
                if (length_modifier == 1) {
                    value = va_arg(args, unsigned long);
                } else if (length_modifier == -1) {
                    value = (unsigned short)va_arg(args, unsigned int);
                } else {
                    value = va_arg(args, unsigned int);
                }
                if (*format == 'x') {
                    if (flag_hash) {
                        buffer_index += sprintf(&buffer[buffer_index], "0x%x", value);
                    } else {
                        buffer_index += sprintf(&buffer[buffer_index], "%x", value);
                    }
                } else {
                    if (flag_hash) {
                        buffer_index += sprintf(&buffer[buffer_index], "0X%X", value);
                    } else {
                        buffer_index += sprintf(&buffer[buffer_index], "%X", value);
                    }
                }
            }

            format++;  // skip conversion specifier
        } else {
            buffer[buffer_index++] = *format++;
        }

        // Flush buffer if necessary
        if (buffer_index >= sizeof(buffer) - 1) {
            write(STDOUT_FILENO, buffer, buffer_index);
            count += buffer_index;
            buffer_index = 0;
        }
    }

    // Flush remaining buffer
    if (buffer_index > 0) {
        write(STDOUT_FILENO, buffer, buffer_index);
        count += buffer_index;
    }

    va_end(args);

    return count;
}
