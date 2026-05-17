#include "shell.h"

/**
 * main - entry point
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("#cisfun$ ");

		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break;

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (line[0] != '\0')
			execute_command(line);
	}

	free(line);
	return (0);
}
