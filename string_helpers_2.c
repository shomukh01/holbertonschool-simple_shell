#include "shell.h"

/**
 * _atoi - Converts a string to an integer with strict positive validation
 * @s: The string to convert
 *
 * Return: The converted integer, or -1 if the string contains non-digits
 */
int _atoi(char *s)
{
	int i = 0;
	unsigned int result = 0;

	if (!s)
		return (-1);

	/* Check for leading signs or empty input */
	if (s[0] == '-' || s[0] == '+')
		return (-1);

	while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result = (result * 10) + (s[i] - '0');
			/* Avoid integer overflow handles */
			if (result > 2147483647)
				return (-1);
		}
		else
		{
			return (-1);
		}
		i++;
	}

	return ((int)result);
}
