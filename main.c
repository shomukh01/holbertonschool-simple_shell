#include "shell.h"
#include <string.h>

/**
 * main - entry point
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	char *command;
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

		command = strtok(line, " ");

		if (command != NULL)
			execute_command(command);
	}

	free(line);
	return (0);
}