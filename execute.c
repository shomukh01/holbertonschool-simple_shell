#include "shell.h"

/**
 * execute_command - Forks a child process and executes a command
 * @full_path: The full validated path of the command (e.g., /bin/ls)
 * @args: Array of strings containing the command and its arguments
 */
void execute_command(char *full_path, char **args)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Fork failure");
		return;
	}

	if (child_pid == 0)
	{
		/* Execute the command with the current environment variables */
		if (execve(full_path, args, environ) == -1)
		{
			perror("Execution error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process waits for the child process to complete */
		wait(&status);
	}
}
