#include "shell.h"

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

	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		free(line);
		exit(last_status);
	}

	return (0);
}
