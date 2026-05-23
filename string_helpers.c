#include "shell.h"

/**
 * _strlen - Computes the length of a string
 * @s: The string to measure
 *
 * Return: The length of the string
 */
size_t _strlen(const char *s)
{
	size_t len = 0;

	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

/**
 * _strcmp - Compares two strings
 * @s1: First string
 * @s2: Second string
 *
 * Return: 0 if equal, positive/negative otherwise
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * _strncmp - Compares up to n bytes of two strings
 * @s1: First string
 * @s2: Second string
 * @n: Maximum number of bytes to compare
 *
 * Return: 0 if equal up to n bytes, positive/negative otherwise
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i = 0;

	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}
