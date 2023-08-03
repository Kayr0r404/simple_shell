#include "shell.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
void _putchar(char c)
{
	write(1, &c, 1);
}

/**
 * _putstr - custom function to print a string using low-level I/O
 * @str: string to be printed
 */
void _putstr(const char *str)
{
	write(STDOUT_FILENO, str, _strlen(str));
}

/**
 * _printf - Custom version of printf for strings
 * @format: input string
 */
void _printf(const char *format, ...)
{
	va_list args;

	va_start(args, format);

	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++; /* Move past '%'*/
			if (*format == 's')
			{
				char *str_arg = va_arg(args, char *);

				_putstr(str_arg);
			}
		}
		else
			_putchar(*format);
		format++; /* Move to the next character*/
	}

	va_end(args);
}
