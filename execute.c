#include "shell.h"

/**
 * execute_command - Forks a child process and executes a command
 * @full_path: The full validated path of the command
 * @args: Array of strings containing the command and arguments
 * Return: The exit status of the executed command
 */
int execute_command(char *full_path, char **args)
{
	pid_t child_pid;
	int status;
	int exit_status = 0;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Fork failure");
		return (1);
	}

	if (child_pid == 0)
	{
		if (execve(full_path, args, environ) == -1)
		{
			perror("Execution error");
			exit(127);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
	}
	return (exit_status);
}
