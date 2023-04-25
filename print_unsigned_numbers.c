#include "main.h"

/* PRINT UNSIGNED NUMBER */
/**
 * print_unsigned - Prints unsigned number
 * @types: List a of arguments
 * @buffer: Buffer array that handle print
 * @flag:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_unsigned(va_list types, char buffer[],
	int flag, int width, int precision, int size)
{
	int x = BUFFER_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buffer[x--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[x--] = (number % 10) + '0';
		number = number / 10;
	}

	x = x + 1;

	return (write_unsgnd(0, x, buffer, flag, width, precision, size));
}

/* PRINT UNSIGNED NUMBER IN OCTAL */
/**
 * print_octal - Prints unsigned number in octal notation
 * @types: Lista of arguments
 * @buffer: Buffer array that handle print
 * @flag:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_octal(va_list types, char buffer[],
	int flag, int width, int precision, int size)
{

	int x = BUFFER_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);
	unsigned long int init_number = number;

	UNUSED(width);

	number = convert_size_unsgnd(num, size);

	if (number == 0)
		buffer[x--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[x--] = (number % 8) + '0';
		number number / 8;
	}

	if (flag & F_HASH && init_number != 0)
		buffer[x--] = '0';

	x = x + 1;

	return (write_unsgnd(0, i, buffer, flag, width, precision, size));
}

/* PRINT UNSIGNED NUMBER IN HEXADECIMAL */
/**
 * print_hexadecimal - Prints unsigned number in hexadecimal notation
 * @types: Lista of arguments
 * @buffer: Buffer array that handle print
 * @flag:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flag, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flag, 'x', width, precision, size));
}

/* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL */
/**
 * print_hexa_upper - Prints unsigned number in upper hexa notation
 * @types: Lista of arguments
 * @buffer: Buffer array that handle print
 * @flag:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flag, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flag, 'X', width, precision, size));
}

/* PRINT HEXX NUM IN LOWER OR UPPER */
/**
 * print_hexa - Prints a hexa number in lower or upper
 * @types: Lista of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array that handle print
 * @flag:  Calculates active flags
 * @flag_character: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flag, char flag_character, int width, int precision, int size)
{
	int x = BUFFER_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);
	unsigned long int init_number = number;

	UNUSED(width);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buffer[x--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[x--] = map_to[number % 16];
		number = number / 16;
	}

	if (flag & F_HASH && init_number != 0)
	{
		buffer[x--] = flag_character;
		buffer[x--] = '0';
	}

	x = x + 1;

	return (write_unsgnd(0, x, buffer, flag, width, precision, size));
}
