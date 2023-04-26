#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string to print the arguments
 * @i: List of arguments that will be printed.
 *
 * Return: Precision.
 */

int get_size(const char *format, int *i)
{
	int current_i = *i + 1;
	int size = 0;

	if (format[current_i] == 'l')
		size = S_LONG;
	
	else if (format[current_i] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = current_i - 1;
	else
		*i = current_i;

	return (size);
}
