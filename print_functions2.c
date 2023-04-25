#include "main.h"

/*PRINT POINTER*/

/**
 * print_pointer - Prints the value of pointer variable
 * @types: List of arguments
 * @buffer: Buffer array
 * @flags:  Calculates active flags
 * @width: width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */

int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_char = 0, padd = ' ';
	int index = BUFFER_SIZE - 2, len = 2, padd_start = 1;
	unsigned long n_address;
	char map[] = "0123456789abcdef";
	void *address = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (address == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFFER_SIZE - 1] = '\0';
	UNUSED(precision);

	n_address = (unsigned long)address;

	while (n_address > 0)
	{
		buffer[index--] = map[n_address % 16];
		n_address /= 16;
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_char = '+', len++;
	else if (flags & F_SPACE)
		extra_char = ' ', len++;

	index++;

	return (write_pointer(buffer, index, len,
		width, flags, padd, extra_char, padd_start));
}

/*PRINT NON PRINTABLE*/

/**
 * print_non_printable - Prints ASCII codes in hexadec of non printable chars
 * @types: List of arguments
 * @buffer: Buffer array
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars that is printed
 */

int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int itr = 0, offset = 0;
	char *s = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (s == NULL)
		return (write(1, "(null)", 6));

	while (s[itr] != '\0')
	{
		if (is_printable(s[itr]))
			buffer[itr + offset] = s[itr];
		else
			offset += append_hexa_code(s[itr], buffer, itr + offset);

		itr++;
	}

	buffer[itr + offset] = '\0';

	return (write(1, buffer, itr + offset));
}

/*PRINT REVERSE*/

/**
 * print_reverse - Prints the reverse of string.
 * @types: List of arguments
 * @buffer: Buffer array
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *s;
	int itr, counter = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	s = va_arg(types, char *);

	if (s == NULL)
	{
		UNUSED(precision);

		s = ")Null(";
	}
	for (itr = 0; s[itr]; itr++)
		;

	for (itr = itr - 1; itr >= 0; itr--)
	{
		char x = s[itr];

		write(1, &x, 1);
		counter++;
	}
	return (counter);
}

/*PRINT A STRING IN ROT13*/

/**
 * print_rot13string - Print a string in rot13 format
 * @types: List of arguments
 * @buffer: Buffer array
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c;
	char *s;
	unsigned int itr, itr2;
	int counter = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	s = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (s == NULL)
		s = "(AHYY)";
	for (itr = 0; s[itr]; itr++)
	{
		for (itr2 = 0; in[itr2]; itr2++)
		{
			if (in[itr2] == str[itr])
			{
				c = out[itr2];
				write(1, &c, 1);
				counter++;
				break;
			}
		}
		if (!in[itr2])
		{
			c = s[itr];
			write(1, &c, 1);
			counter++;
		}
	}
	return (counter);
}
