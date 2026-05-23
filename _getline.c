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
			/* Replaced fileno with STDIN_FILENO to pass allowed functions test */
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
			*n *= 2;
			*lineptr = realloc(*lineptr, *n);
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
