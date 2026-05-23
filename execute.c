#include "shell.h"

/**
 * execute_command - Executes built-ins or forks a process to run external binaries
 * @args: Array of tokenized arguments/commands
 * @shell_name: Name of the shell executable for error reporting
 * @line: The raw input line buffer passed for memory cleanup
 * @status: The last executed command's exit status
 *
 * Return: Status code of the executed command or built-in
 */
int execute_command(char **args, char *shell_name, char *line, int status)
{
	int builtin_status;
	pid_t child_pid;
	char *actual_command;

	if (args == NULL || args[0] == NULL)
		return (status);

	/* Pass the current running status dynamically to built-ins */
	builtin_status = check_builtins(args, status, shell_name, line);
	if (builtin_status != -1)
		return (builtin_status);

	actual_command = find_path(args[0]);
	if (actual_command == NULL)
	{
		write(STDERR_FILENO, shell_name, _strlen(shell_name));
		write(STDERR_FILENO, ": 1: ", 5);
		write(STDERR_FILENO, args[0], _strlen(args[0]));
		write(STDERR_FILENO, ": not found\n", 12);
		return (127);
	}

	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve(actual_command, args, environ) == -1)
		{
			perror(shell_name);
			exit(EXIT_FAILURE);
		}
	}
	else if (child_pid < 0)
	{
		perror(shell_name);
		if (actual_command != args[0])
			free(actual_command);
		return (1);
	}
	else
	{
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}

	if (actual_command != args[0])
		free(actual_command);

	return (status);
}
