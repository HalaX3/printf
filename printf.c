#include "main.h"

void print_buffer(char buffer_arr[], int *buffer_index);

/**
 * _printf - function to print
 * @format: format.
 * Return: Printed chars.
 */

int _printf(const char *format, ...)
{
	int itr, chars_printed = 0, printed_chars = 0;
	int flag, w, precision, size, buffer_index = 0;
	va_list list;
	char buffer[BUFFER_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (itr = 0; format && format[itr] != '\0'; itr++)
	{
		if (format[itr] != '%')
		{
			buffer[buffer_index++] = format[itr];
			if (buffer_index == BUFFER_SIZE)
				print_buffer(buffer, &buffer_index);
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buffer_index);
			flag = get_flags(format, &itr);
			w = get_width(format, &itr, list);
			precision = get_precision(format, &itr, list);
			size = get_size(format, &itr);
			++itr;
			chars_printed = handle_print(format, &itr, list, buffer,
				flag, w, precision, size);
			if (chars_printed == -1)
				return (-1);
			printed_chars += chars_printed;
		}
	}

	print_buffer(buffer, &buffer_index);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer_arr: Array of chars
 * @buffer_index: Index at which to add next char, represents the length.
 */

void print_buffer(char buffer_arr[], int *buffer_index)
{
	if (*buffer_index > 0)
		write(1, &buffer_arr[0], *buffer_index);

	*buffer_index = 0;
}
