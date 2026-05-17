#include "shell.h"

/**
 * execute_command - execute a command
 * @command: command to execute
 *
 * Return: Nothing
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;
	char *args[2];

	args[0] = command;
	args[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		if (execve(command, args, environ) == -1)
		{
			perror("./hsh");
			exit(127);
		}
	}

	wait(&status);
}
