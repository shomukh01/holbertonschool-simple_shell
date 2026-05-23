#include "shell.h"

/**
 * _getline - Reads an entire line from a stream using a static buffer
 * @lineptr: Buffer that stores the read line
 * @n: Size of the lineptr buffer
 * @stream: Stream to read from (usually stdin)
 *
 * Return: Number of bytes read, or -1 on failure or EOF
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[1024];
	static size_t buf_pos;
	static size_t buf_size;
	size_t count = 0;
	size_t old_n;
	char c;
	(void)stream;

	if (lineptr == NULL || n == NULL)
		return (-1);
	if (*lineptr == NULL || *n == 0)
	{
		*n = 128;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
	while (1)
	{
		if (buf_pos >= buf_size)
		{
			int bytes_read = read(STDIN_FILENO, buffer, 1024);

			if (bytes_read <= 0)
			{
				if (count == 0)
					return (-1);
				break;
			}
			buf_size = bytes_read;
			buf_pos = 0;
		}
		c = buffer[buf_pos++];
		if (count >= *n - 1)
		{
			old_n = *n;
			*n *= 2;
			/* Replaced standard realloc with custom implementation to pass tests */
			*lineptr = _realloc(*lineptr, old_n, *n);
			if (*lineptr == NULL)
				return (-1);
		}
		(*lineptr)[count++] = c;
		if (c == '\n')
			break;
	}
	(*lineptr)[count] = '\0';
	return (count);
}
