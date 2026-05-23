#include "shell.h"

/**
 * execute_logical - Parses and executes commands with && and || operators
 * @line: The raw input line from the user
 * @shell_name: Name of the shell executable for error reporting
 * @status: The current tracking exit status
 *
 * Return: Status of the last executed command
 */
int execute_logical(char *line, char *shell_name, int status)
{
	char **commands = NULL;
	char *operators[100];
	int i = 0, j = 0, op_count = 0;
	int k;

	commands = malloc(sizeof(char *) * 100);
	if (!commands)
		return (1);

	for (k = 0; k < 100; k++)
	{
		commands[k] = NULL;
		operators[k] = NULL;
	}

	commands[i] = _strtok(line, " \t\r\n\a");
	while (commands[i] != NULL && i < 99)
	{
		if (_strcmp(commands[i], "&&") == 0 || _strcmp(commands[i], "||") == 0)
		{
			operators[op_count++] = commands[i];
			commands[i] = NULL;
		}
		i++;
		commands[i] = _strtok(NULL, " \t\r\n\a");
	}

	while (commands[j] != NULL)
	{
		char **args = &commands[j];
		int next_j = j;

		while (commands[next_j] != NULL)
			next_j++;

		/* Pass and update the status dynamically */
		status = execute_command(args, shell_name, line, status);

		if (j / 2 < op_count)
		{
			char *op = operators[j / 2];

			if (op != NULL)
			{
				if (_strcmp(op, "&&") == 0 && status != 0)
					break;
				if (_strcmp(op, "||") == 0 && status == 0)
					break;
			}
		}
		j = next_j + 1;
	}
	free(commands);
	return (status);
}
