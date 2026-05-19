#include "shell.h"

/**
 * handle_sigint - Handles the SIGINT signal (Ctrl+C)
 * @sig: The signal number
 *
 * Return: void
 */
void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n#cisfun$ ", 10);
}

/**
 * main - Entry point for the custom simple shell
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: Status of the last executed command
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int status = 0;
	(void)ac;

	signal(SIGINT, handle_sigint);

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(status);
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (strlen(line) > 0)
		{
			status = execute_logical(line, av[0]);
		}
	}
	free(line);
	return (status);
}
