#include "shell.h"

/**
 * handle_sigint - Signal handler for SIGINT (Ctrl+C)
 * @sig: The signal number
 */
void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * main - Entry point for the custom simple shell
 * @ac: Argument count
 * @av: Argument vector containing program name and parameters
 *
 * Return: The final exit status of the shell execution
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read_bytes;
	int status = 0;
	int is_interactive = isatty(STDIN_FILENO);

	(void)ac;

	/* Register custom signal handler for Ctrl+C to maintain prompt */
	signal(SIGINT, handle_sigint);

	while (1)
	{
		/* Display prompt only in interactive mode */
		if (is_interactive)
			write(STDOUT_FILENO, "$ ", 2);

		read_bytes = _getline(&line, &len, stdin);

		/* Handle End-Of-File (EOF) / Ctrl+D conditions safely */
		if (read_bytes == -1)
		{
			if (is_interactive)
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			return (status);
		}

		/* Process the line if it is not just an empty newline character */
		if (read_bytes > 1 && line[0] != '\n')
		{
			/* Dynamically maintain and update the exit status */
			status = execute_logical(line, av[0], status);
		}
	}

	free(line);
	return (status);
}
