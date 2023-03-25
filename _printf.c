#include <stdarg.h>
#include <stdio.h>
#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
* _printf - Printf function
* @format: format.
* Return: Printed chars.
**/

int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;
	char c;

va_start(args, format);

	while (*format != '\0')
{
	if (*format == '%')
	{
format++;  // skip '%'

	switch (*format)
		{
		case 'c':
		c = (char) va_arg(args, int);
		putchar(c);
		count++;
		break;

		case 's':
		const char *s = va_arg(args, const char *);
		while (*s != '\0')
			{
			putchar(*s);
			s++;
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

}

else

{
putchar(*format);
count++;
}

format++;

}

va_end(args);

return count;

}
