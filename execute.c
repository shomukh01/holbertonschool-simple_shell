#include "shell.h"

/**
 * execute_command - execute command
 * @args: command arguments
 *
 * Return: Nothing
 */
void execute_command(char **args)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror("./hsh");
			exit(127);
		}
	}

	wait(&status);
}
