#include "shell.h"

/**
 * print_env - Prints all environment variables to standard output
 *
 * Return: void
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
 * check_builtins - Evaluates if a command is a shell builtin
 * @args: Array of tokenized arguments
 * @status: Current exit status to return on exit command
 *
 * Return: Builtin execution status, or -1 if not a builtin
 */
int check_builtins(char **args, int status)
{
	if (!args[0])
		return (-1);

	if (_strcmp(args[0], "exit") == 0)
	{
		free(args[0]);
		exit(status);
	}

	if (_strcmp(args[0], "env") == 0)
	{
		print_env();
		return (0);
	}

	return (-1);
}
