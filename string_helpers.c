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

/**
 * _realloc - Reallocates a memory block using malloc and free
 * @ptr: Pointer to the previous memory block
 * @old_size: Size in bytes of the allocated space for ptr
 * @new_size: New size in bytes of the new memory block
 *
 * Return: Pointer to the newly allocated memory block, or NULL on failure
 */
void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
	char *new_ptr;
	char *old_ptr;
	size_t i;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_ptr = (char *)ptr;
	for (i = 0; i < old_size && i < new_size; i++)
		new_ptr[i] = old_ptr[i];

	free(ptr);
	return (new_ptr);
}

/**
 * _strtok - Custom tokenization function replacing standard strtok
 * @str: The string to split into tokens
 * @delim: The delimiter characters
 *
 * Return: Pointer to the next token, or NULL if no more tokens are found
 */
char *_strtok(char *str, const char *delim)
{
	static char *current_token;
	char *token_start;
	int i, is_delim;

	if (str != NULL)
		current_token = str;

	if (current_token == NULL || *current_token == '\0')
		return (NULL);

	while (*current_token != '\0')
	{
		is_delim = 0;
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*current_token == delim[i])
			{
				is_delim = 1;
				break;
			}
		}
		if (!is_delim)
			break;
		current_token++;
	}

	if (*current_token == '\0')
		return (NULL);

	token_start = current_token;

	while (*current_token != '\0')
	{
		is_delim = 0;
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*current_token == delim[i])
			{
				is_delim = 1;
				break;
			}
		}
		if (is_delim)
		{
			*current_token = '\0';
			current_token++;
			break;
		}
		current_token++;
	}

	return (token_start);
}
