#include "shell.h"

/**
 * execute_command - Forks a process and executes a command
 * @args: Array of arguments passed to the command
 * @shell_name: Name of the shell program
 *
 * Return: Exit status of the executed command
 */
int execute_command(char **args, char *shell_name)
{
	pid_t pid;
	int status = 0, builtin_status;
	char *full_path = NULL;

	builtin_status = check_builtins(args, status);
	if (builtin_status != -1)
		return (builtin_status);

	full_path = find_path(args[0]);
	if (!full_path)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", shell_name, args[0]);
		return (127);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(full_path, args, environ) == -1)
		{
			perror(shell_name);
			exit(1);
		}
	}
	else if (pid < 0)
	{
		perror(shell_name);
		return (1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}

	if (full_path != args[0])
		free(full_path);

	return (status);
}
