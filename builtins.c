#include "shell.h"

/**
 * check_builtin - Checks if the parsed command is a built-in command
 * @args: Array of arguments (command and its options)
 * Return: 1 if it is a built-in (like exit), 0 otherwise
 */
int check_builtin(char **args)
{
	if (args == NULL || args[0] == NULL)
		return (0);

	/* Compare the command with "exit" */
	if (strcmp(args[0], "exit") == 0)
	{
		return (1);
	}

	return (0);
}
