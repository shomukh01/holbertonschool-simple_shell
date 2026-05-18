#include "shell.h"

/**
 * print_env - Prints the current environment variables
 * Return: void
 */
void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

/**
 * check_builtin - Checks if the parsed command is a built-in command
 * @args: Array of arguments (command and its options)
 * @line: The input line to free before exit
 * @last_status: The last executed command's exit status
 * Return: 1 if it is a built-in, 0 otherwise
 */
int check_builtin(char **args, char *line, int last_status)
{
	if (args == NULL || args[0] == NULL)
		return (0);

	/* Check for exit built-in */
	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		free(line);
		exit(last_status);
	}

	/* Task 6: Check for env built-in */
	if (strcmp(args[0], "env") == 0)
	{
		print_env();
		return (1);
	}

	return (0);
}
