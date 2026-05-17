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
	char *args[10];
	char *token;
	size_t len = 0;
	ssize_t nread;
	int i;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("#cisfun$ ");

		nread = getline(&line, &len, stdin);

		if (nread == -1)
			break;

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		token = strtok(line, " ");
		i = 0;

		while (token != NULL)
		{
			args[i] = token;
			token = strtok(NULL, " ");
			i++;
		}

		args[i] = NULL;

		if (args[0] != NULL)
			execute_command(args);
	}

	free(line);
	return (0);
}
