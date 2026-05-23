#include "shell.h"

/**
 * main - Entry point for the simple shell program
 * @ac: Argument count
 * @av: Argument vector (contains shell name at av[0])
 *
 * Return: 0 on success, or status code on exit
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t bytes_read;
	int status = 0;
	(void)ac;
	(void)av;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		bytes_read = getline(&line, &len, stdin);
		if (bytes_read == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			free_env_vars();
			exit(status);
		}
	}
	return (status);
}
