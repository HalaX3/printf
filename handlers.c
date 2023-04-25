#include "main.h"

/* WRITE HANDLE */
/**
 * handle_write_char - Prints a string
 * @character: char types.
 * @buffer: Buffer array to handle print
 * @flag:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char character, char buffer[],
	int flag, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
	int x = 0;
	char padding = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flag & F_ZERO)
		padding = '0';

	buffer[x++] = character;
	buffer[x] = '\0';

	if (width > 1)
	{
		buffer[BUFFER_SIZE - 1] = '\0';
		for (x = 0; x < width - 1; x++)
			buffer[BUFFER_SIZE - x - 2] = padding;

		if (flag & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFFER_SIZE - x - 1], width - 1));
		else
			return (write(1, &buffer[BUFFER_SIZE - x - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/* WRITE NUMBER */
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @index: char types.
 * @buffer: Buffer array to handle print
 * @flag:  Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int index, char buffer[],
	int flag, int width, int precision, int size)
{
	int length = BUFFER_SIZE - index - 1;
	char padding = ' ', extra_character = 0;

	UNUSED(size);

	if ((flag & F_ZERO) && !(flag & F_MINUS))
		padding = '0';
	if (is_negative)
		extra_character = '-';
	else if (flag & F_PLUS)
		extra_character = '+';
	else if (flag & F_SPACE)
		extra_character = ' ';

	return (write_num(index, buffer, flag, width, precision,
		length, padding, extra_character));
}

/**
 * write_num - Write a number using a bufffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flag: Flags
 * @width: width
 * @precis: Precision specifier
 * @length: Number length
 * @padding: Pading char
 * @extra_character: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char buffer[],
	int flag, int width, int precis,
	int length, char padding, char extra_character)
{
	int x, padding_start = 1;

	if (precis == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (precis == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padding = ' ';
	if (precis > 0 && precis < length)
		padding = ' ';
	while (precis > length)
		buffer[--ind] = '0', length++;
	if (extra_character != 0)
		length++;
	if (width > length)
	{
		for (x = 1; x < width - length + 1; x++)
			buffer[x] = padding;
		buffer[x] = '\0';
		if (flag & F_MINUS && padding == ' ')
		{
			if (extra_character)
				buffer[--ind] = extra_character;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], x - 1));
		}
		else if (!(flag & F_MINUS) && padding == ' ')
		{
			if (extra_character)
				buffer[--ind] = extra_character;
			return (write(1, &buffer[1], x - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flag & F_MINUS) && padding == '0')
		{
			if (extra_character)
				buffer[--padding_start] = extra_character;
			return (write(1, &buffer[padding_start], x - padding_start) +
				write(1, &buffer[ind], length - (1 - padding_start)));
		}
	}
	if (extra_character)
		buffer[--ind] = extra_character;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @index: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flag: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int index,
	char buffer[],
	int flag, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position x */
	int length = BUFFER_SIZE - index - 1, x = 0;
	char padding = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && index == BUFFER_SIZE - 2 && buffer[index] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		padding = ' ';

	while (precision > length)
	{
		buffer[--index] = '0';
		length++;
	}

	if ((flag & F_ZERO) && !(flag & F_MINUS))
		padding = '0';

	if (width > length)
	{
		for (x = 0; x < width - length; x++)
			buffer[x] = padding;

		buffer[x] = '\0';

		if (flag & F_MINUS) /* Asign extra char to left of buffer [buffer>padding]*/
		{
			return (write(1, &buffer[index], length) + write(1, &buffer[0], x));
		}
		else /* Asign extra char to left of padding [padding>buffer]*/
		{
			return (write(1, &buffer[0], x) + write(1, &buffer[index], length));
		}
	}

	return (write(1, &buffer[index], length));
}

/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @index: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Width specifier
 * @flag: Flags specifier
 * @padding: Char representing the padding
 * @extra_character: Char representing extra char
 * @padding_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int index, int length,
	int width, int flag, char padding, char extra_character, int padding_start)
{
	int x;

	if (width > length)
	{
		for (x = 3; x < width - length + 3; x++)
			buffer[x] = padding;
		buffer[x] = '\0';
		if (flag & F_MINUS && padding == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extra_character)
				buffer[--index] = extra_ character;
			return (write(1, &buffer[index], length) + write(1, &buffer[3], x - 3));
		}
		else if (!(flag & F_MINUS) && padding == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extra_character)
				buffer[--index] = extra_ character;
			return (write(1, &buffer[3], x - 3) + write(1, &buffer[index], length));
		}
		else if (!(flag & F_MINUS) && padding == '0')/* extra c to left of padd */
		{
			if (extra_ character)
				buffer[--padding_start] = extra_ character;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padding_start], x - padding_start) +
				write(1, &buffer[index], length - (1 - padding_start) - 2));
		}
	}
	buffer[--index] = 'x';
	buffer[--index] = '0';
	if (extra_character
		buffer[--index] = extra_ character;
	return (write(1, &buffer[index], BUFFER_SIZE - index - 1));
}
