#include "main.h"

/*PRINT CHAR*/

/**
 * print_char - Prints a char
 * @types: List of arguments
 * @buffer: Buffer array
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_char(va_list types, char buffer[], int flags,
	int width, int precision, int size)
{
	char x = va_arg(types, int);

	return (handle_write_char(x, buffer, flags, width, precision, size));
}

/*PRINT A STRING*/

/**
 * print_string - Prints a string
 * @types: List of arguments
 * @buffer: Buffer array
 * @flags:  Calculates active flags
 * @width: get the width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_string(va_list types, char buffer[], int flags,
	int width, int precision, int size)
{
	int len = 0, itr;
	char *s = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (s == NULL)
	{
		s = "(null)";
		if (precision >= 6)
			s = "      ";
	}
	while (s[len] != '\0')
		len++;
	if (precision >= 0 && precision < len)
		len = precision;
	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &s[0], len);
			for (itr = width - len; itr > 0; itr--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (itr = width - len; itr > 0; itr--)
				write(1, " ", 1);
			write(1, &s[0], len);
			return (width);
		}
	}
	return (write(1, s, len));
}

/*PRINT PERCENT SIGN*/

/**
 * print_percent - Prints a percent sign
 * @types: List of arguments
 * @buffer: Buffer array
 * @flags:  Calculates active flags
 * @width: get the width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_percent(va_list types, char buffer[], int flags,
	int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	return (write(1, "%%", 1));
}

/*PRINT INT*/

/**
 * print_int - Print int
 * @types: List of arguments
 * @buffer: Buffer array
 * @flags:  Calculates active flags
 * @width: get the width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_int(va_list types, char buffer[], int flags,
	int width, int precision, int size)
{
	int itr = BUFFER_SIZE - 2;
	int is_neg = 0;
	long int num = va_arg(types, long int);
	unsigned long int number;

	num = convert_size_number(num, size);

	if (num == 0)
		buffer[itr--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';
	number = (unsigned long int)num;

	if (num < 0)
	{
		number = (unsigned long int)((-1) * num);
		is_neg = 1;
	}

	while (number > 0)
	{
		buffer[itr--] = (number % 10) + '0';
		number /= 10;
	}

	itr++;

	return (write_number(is_neg, itr, buffer, flags, width, precision, size));
}

/*PRINT BINARY*/

/**
 * print_binary - Prints an unsigned number
 * @types: List of arguments
 * @buffer: Buffer array
 * @flags:  Calculates active flags
 * @width: get the width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */

int print_binary(va_list types, char buffer[], int flags,
	int width, int precision, int size)
{
	unsigned int num, x, itr, sum;
	unsigned int arr[32];
	int counter;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	num = va_arg(types, unsigned int);
	x = 2147483648;
	arr[0] = num / x;
	for (itr = 1; itr < 32; itr++)
	{
		x /= 2;
		arr[itr] = (num / x) % 2;
	}
	for (itr = 0, sum = 0, counter = 0; itr < 32; itr++)
	{
		sum += arr[itr];
		if (sum || itr == 31)
		{
			char y = '0' + arr[itr];

			write(1, &y, 1);
			counter++;
		}
	}
	return (counter);
}
