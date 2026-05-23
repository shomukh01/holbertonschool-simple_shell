/**
 * check_builtins - Checks and executes built-in shell commands
 * @args: Array of tokenized arguments
 * @status: The current exit status of the last executed command
 * @shell_name: Name of the shell program for printing custom errors
 * @line: The raw buffer line to free before exiting to prevent memory leaks
 *
 * Return: 0 or positive status if built-in executed, -1 if not a built-in
 */
int check_builtins(char **args, int status, char *shell_name, char *line)
{
	if (_strcmp(args[0], "exit") == 0)
		return (handle_exit(args, status, shell_name, line));

	if (_strcmp(args[0], "env") == 0)
	{
		print_env();
		return (0);
	}
	if (_strcmp(args[0], "setenv") == 0)
	{
		/* If parameters are missing, just return 0 to continue execution smoothly */
		if (!args[1] || !args[2])
		{
			return (0);
		}
		if (_setenv(args[1], args[2]) == -1)
		{
			/* Fail silently or handle internal error without crashing the flow */
			return (0);
		}
		return (0);
	}
	if (_strcmp(args[0], "unsetenv") == 0)
	{
		/* If parameter is missing, return 0 and skip silently */
		if (!args[1])
		{
			return (0);
		}
		if (_unsetenv(args[1]) == -1)
		{
			return (0);
		}
		return (0);
	}
	return (-1);
}
