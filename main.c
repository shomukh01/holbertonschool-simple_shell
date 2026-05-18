#include "shell.h"

/**
 * handle_input - Process and execute the parsed command arguments
 * @line: The raw input string from getline
 * Return: void
 */
void handle_input(char *line)
{
	char **args;
	char *full_path;

	args = tokenize_input(line);
	if (args && args[0])
	{
		/* Task 5: Check for exit built-in command */
		if (check_builtin(args) == 1)
		{
			free(args);
			free(line);
			exit(EXIT_SUCCESS);
		}

		/* Task 4: Search for command in PATH */
		full_path = find_path(args[0]);
		if (full_path == NULL)
		{
			fprintf(stderr, "./shell: 1: %s: not found\n", args[0]);
		}
		else
		{
			/* Task 2 & 3: Execute command with arguments */
			execute_command(full_path, args);
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

	while (1)
	{
		/* Print prompt only if in interactive mode */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(EXIT_SUCCESS);
		}

		/* Remove trailing newline character */
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		/* Call helper function to process commands */
		handle_input(line);
	}
	free(line);
	return (0);
}
