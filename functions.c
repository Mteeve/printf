#include <stdarg.h>
#include <unistd.h>

#define BUFF_SIZE 1024

int handle_write_char(char c, char buffer[], int flags, int width, int precision, int size) {
    // implementation
}

long int convert_size_number(long int n, int size) {
    // implementation
}

int write_number(int is_negative, int i, char buffer[], int flags, int width, int precision, int size) {
    // implementation
}

/************************* PRINT CHAR *************************/

int print_char(va_list types, char buffer[],
    int flags, int width, int precision, int size) {
    char c = va_arg(types, int);

    return (handle_write_char(c, buffer, flags, width, precision, size));
}

/************************* PRINT A STRING *************************/

int print_string(va_list types, char buffer[],
    int flags, int width, int precision, int size) {
    int length = 0, i;
    char *str = va_arg(types, char *);

    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);
    if (str == NULL) {
        str = "(null)";
        if (precision >= 6)
            str = "      ";
    }

    while (str[length] != '\0')
        length++;

    if (precision >= 0 && precision < length)
        length = precision;

    if (width > length) {
        if (flags & F_MINUS) {
            write(1, &str[0], length);
            for (i = width - length; i > 0; i--)
                write(1, " ", 1);
            return (width);
        }
        else {
            for (i = width - length; i > 0; i--)
                write(1, " ", 1);
            write(1, &str[0], length);
            return (width);
        }
    }

    return (write(1, str, length));
}

/************************* PRINT PERCENT SIGN *************************/

int print_percent(va_list types, char buffer[],
    int flags, int width, int precision, int size) {
    UNUSED(types);
    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);
    return (write(
