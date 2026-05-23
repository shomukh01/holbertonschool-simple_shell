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
	int i = 0, len;
	char *new_var;

	if (!variable || _strlen(variable) == 0)
		return (-1);

	/* If value is NULL, treat it as an empty string "" */
	if (!value)
		value = "";

	/* Calculate space needed for VARIABLE=VALUE\0 */
	len = _strlen(variable) + _strlen(value) + 2;
	new_var = malloc(len);
	if (!new_var)
		return (-1);

	/* Construct the string "VARIABLE=VALUE" */
	i = 0;
	while (*variable)
		new_var[i++] = *variable++;
	new_var[i++] = '=';
	while (*value)
		new_var[i++] = *value++;
	new_var[i] = '\0';

	/* Check if variable already exists */
	i = 0;
	while (environ[i])
	{
		if (_strncmp(environ[i], new_var, _strlen(variable)) == 0 &&
			environ[i][_strlen(variable)] == '=')
		{
			environ[i] = new_var; /* Overwrite existing value */
			return (0);
		}
		i++;
	}

	/* If it doesn't exist, append it to environment array */
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
	int i = 0, j;
	int len;

	if (!variable || _strlen(variable) == 0)
		return (-1);

	len = _strlen(variable);
	while (environ[i])
	{
		/* Look for matching variable name */
		if (_strncmp(environ[i], variable, len) == 0 && environ[i][len] == '=')
		{
			/* Shift all elements upwards to close the gap */
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
	{
		if (args[1] != NULL)
		{
			int exit_code = _atoi(args[1]);

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
	if (_strcmp(args[0], "env") == 0)
	{
		print_env();
		return (0);
	}
	if (_strcmp(args[0], "setenv") == 0)
	{
		/* Case: setenv without parameters -> Display environment */
		if (!args[1])
		{
			print_env();
			return (0);
		}
		/* Case: setenv with only one parameter -> value is empty */
		if (_setenv(args[1], args[2]) == -1)
			write(STDERR_FILENO, "setenv: Failed to set variable\n", 31);
		return (0);
	}
	if (_strcmp(args[0], "unsetenv") == 0)
	{
		/* Case: unsetenv without parameters -> Display environment */
		if (!args[1])
		{
			print_env();
			return (0);
		}
		if (_unsetenv(args[1]) == -1)
			write(STDERR_FILENO, "unsetenv: Failed to unset variable\n", 35);
		return (0);
	}
	return (-1);
}
