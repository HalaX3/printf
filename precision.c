#include "main.h"

/**
 * get_precision - Calculates the precision
 * @format: Formatted string to print the arguments
 * @i: List of arguments that will be printed.
 * @list: list of arguments.
 *
 * Return: Precision.
 */

int get_precision(const char *format, int *i, va_list list)
{
	int current_i = *i + 1;
	int precision_ = -1;

	if (format[current_i] != '.')
		return (precision_);

	precision_ = 0;

	for (current_i += 1; format[current_i] != '\0'; current_i++)
	{
		if (is_digit(format[current_i]))
		{
			precision_ *= 10;
			precision_ += format[current_i] - '0';
		}
		else if (format[current_i] == '*')
		{
			current_i++;
			precision_ = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = current_i - 1;

	return (precision_);
}
