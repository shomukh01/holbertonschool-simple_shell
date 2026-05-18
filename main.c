#include "shell.h"

/**
 * handle_input - Process and execute the parsed command arguments
 * @line: The raw input string from getline
 * @last_status: Pointer to the last exit status integer
 * Return: void
 */
void handle_input(char *line, int *last_status)
{
	char **args;
	char *full_path;

	args = tokenize_input(line);
	if (args && args[0])
	{
		/* Task 5: Check for exit built-in command with last_status */
		if (check_builtin(args, line, *last_status) == 1)
			return;

		/* Task 4: Search for command in PATH */
		full_path = find_path(args[0]);
		if (full_path == NULL)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
			*last_status = 127;
		}
		else
		{
			/* Execute and update the last exit status */
			*last_status = execute_command(full_path, args);
			if (full_path != args[0])
				free(full_path);
		}
	}
	free(args);
}

/**
 * main - Core loop of the simple shell
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int last_status = 0;

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
			exit(last_status);
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		handle_input(line, &last_status);
	}
	free(line);
	return (0);
}
