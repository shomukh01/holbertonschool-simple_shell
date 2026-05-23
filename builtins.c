#include "shell.h"

/**
 * print_env - Prints all the environment variables to stdout
 */
void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

/**
 * _setenv - Initializes a new environment variable, or modifies an existing one
 * @variable: The name of the environment variable
 * @value: The value to assign to the variable
 *
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *variable, const char *value)
{
	int i = 0, len, var_len;
	char *new_var;

	if (!variable || !value || _strlen(variable) == 0)
		return (-1);

	var_len = _strlen(variable);
	len = var_len + _strlen(value) + 2;
	new_var = malloc(len);
	if (!new_var)
		return (-1);

	/* Safely copy variable name without shifting the original pointer */
	i = 0;
	while (variable[i])
	{
		new_var[i] = variable[i];
		i++;
	}
	new_var[i++] = '=';

	/* Copy the value directly after the '=' sign */
	len = 0;
	while (value[len])
	{
		new_var[i++] = value[len++];
	}
	new_var[i] = '\0';

	/* Check if variable already exists using a solid length anchor */
	i = 0;
	while (environ[i])
	{
		if (_strncmp(environ[i], variable, var_len) == 0 &&
			environ[i][var_len] == '=')
		{
			environ[i] = new_var; /* Update inline */
			return (0);
		}
		i++;
	}

	/* Append to the end if it's a completely new variable */
	environ[i] = new_var;
	environ[i + 1] = NULL;
	return (0);
}

/**
 * _unsetenv - Removes an environment variable from the system
 * @variable: The name of the environment variable to remove
 *
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *variable)
{
	int i = 0, j, len;

	if (!variable || _strlen(variable) == 0)
		return (-1);

	len = _strlen(variable);
	while (environ[i])
	{
		if (_strncmp(environ[i], variable, len) == 0 && environ[i][len] == '=')
		{
			j = i;
			while (environ[j])
			{
				environ[j] = environ[j + 1];
				j++;
			}
			return (0);
		}
		i++;
	}
	return (0);
}

/**
 * handle_exit - Handles the exit built-in command safely
 * @args: Array of tokenized arguments
 * @status: The current exit status of the shell
 * @shell_name: Name of the shell program for error printing
 * @line: The raw buffer line to free before exiting
 *
 * Return: 2 on illegal number, or exits the process directly
 */
int handle_exit(char **args, int status, char *shell_name, char *line)
{
	int exit_code;

	if (args[1] != NULL)
	{
		exit_code = _atoi(args[1]);
		if (exit_code == -1)
		{
			write(STDERR_FILENO, shell_name, _strlen(shell_name));
			write(STDERR_FILENO, ": 1: exit: Illegal number: ", 27);
			write(STDERR_FILENO, args[1], _strlen(args[1]));
			write(STDERR_FILENO, "\n", 1);
			return (2);
		}
		free(args);
		if (line)
			free(line);
		exit(exit_code);
	}
	free(args);
	if (line)
		free(line);
	exit(status);
}

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
		if (!args[1] || !args[2])
		{
			write(STDERR_FILENO, "setenv: Invalid syntax\n", 23);
			return (1);
		}
		if (_setenv(args[1], args[2]) == -1)
			write(STDERR_FILENO, "setenv: Failed\n", 15);
		return (0);
	}
	if (_strcmp(args[0], "unsetenv") == 0)
	{
		if (!args[1])
		{
			write(STDERR_FILENO, "unsetenv: Invalid syntax\n", 25);
			return (1);
		}
		if (_unsetenv(args[1]) == -1)
			write(STDERR_FILENO, "unsetenv: Failed\n", 17);
		return (0);
	}
	return (-1);
}
