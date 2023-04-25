#include "main.h"

/**
 * is_printable - Evaluates if a char is printable
 * @character: Char to be evaluated.
 *
 * Return: 1 if character is printable, 0 otherwise
 */

int is_printable(char character)
{
	if (character >= 32 && character < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Append ascci in hexa code to buffer
 * @buffer: Array of chars.
 * @x: Index to start appending.
 * @ascii_code: ASSCI CODE.
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char buffer[], int x)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code = ascii_code * -1;

	buffer[x++] = '\\';
	buffer[x++] = 'x';

	buffer[x++] = map_to[ascii_code / 16];
	buffer[x] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Check if a char is a digit
 * @character: Char to be evaluated
 *
 * Return: 1 if c is a digit, 0 otherwise
 */
int is_digit(char character)
{
	if (character >= '0' && character <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Casts a number to the specified size
 * @number: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: Casted value of num
 */
long int convert_size_number(long int number, int size)
{
	if (size == S_LONG)
		return (number);
	else if (size == S_SHORT)
		return ((short)number);

	return ((int)number);
}

/**
 * convert_size_unsgnd - Casts a number to the specified size
 * @number: Number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of number
 */
long int convert_size_unsgnd(unsigned long int number, int size)
{
	if (size == S_LONG)
		return (number);
	else if (size == S_SHORT)
		return ((unsigned short)number);

	return ((unsigned int)number);
}
