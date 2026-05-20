#include "shell.h"

/**
 * execute_logical - Parses and executes commands with && and || operators
 * @line: The raw input line from the user
 * @shell_name: Name of the shell executable for error reporting
 *
 * Return: Status of the last executed command
 */
int execute_logical(char *line, char *shell_name)
{
	char **commands = NULL;
	char *operators[100];
	int i = 0, j = 0, status = 0, op_count = 0;

	commands = calloc(100, sizeof(char *));
	if (!commands)
		return (1);

	commands[i] = strtok(line, " \t\r\n\a");
	while (commands[i] != NULL)
	{
		if (strcmp(commands[i], "&&") == 0 || strcmp(commands[i], "||") == 0)
		{
			operators[op_count++] = commands[i];
			commands[i] = NULL;
		}
		i++;
		commands[i] = strtok(NULL, " \t\r\n\a");
	}

	while (commands[j] != NULL)
	{
		char **args = &commands[j];
		int next_j = j;

		while (commands[next_j] != NULL)
			next_j++;

		status = execute_command(args, shell_name);

		if (j / 2 < op_count)
		{
			char *op = operators[j / 2];

			if (strcmp(op, "&&") == 0 && status != 0)
				break;
			if (strcmp(op, "||") == 0 && status == 0)
				break;
		}
		j = next_j + 1;
	}
	free(commands);
	return (status);
}
