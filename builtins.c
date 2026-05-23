#include "shell.h"

/**
 * print_env - Prints all the environment variables to stdout
 */
void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

/**
 * check_builtins - Checks and executes built-in shell commands
 * @args: Array of tokenized arguments
 * @status: The current exit status of the last executed command
 * @shell_name: Name of the shell program for printing custom errors
 * @line: The raw buffer line to free before exiting to prevent memory leaks
 *
 * Return: 0 if built-in executed, -1 if command is not a built-in
 */
int check_builtins(char **args, int status, char *shell_name, char *line)
{
	if (_strcmp(args[0], "exit") == 0)
	{
		if (args[1] != NULL)
		{
			int exit_code = _atoi(args[1]);

			if (exit_code == -1)
			{
				write(STDERR_FILENO, shell_name, _strlen(shell_name));
				write(STDERR_FILENO, ": 1: exit: Illegal number: ", 27);
				write(STDERR_FILENO, args[1], _strlen(args[1]));
				write(STDERR_FILENO, "\n", 1);
				return (2);
			}
			free(args);
			if (line)
				free(line);
			exit(exit_code);
		}
		free(args);
		if (line)
			free(line);
		exit(status);
	}

	if (_strcmp(args[0], "env") == 0)
	{
		print_env();
		return (0);
	}

	return (-1);
}
