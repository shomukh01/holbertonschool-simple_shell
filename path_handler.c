#include "shell.h"

/**
 * _getenv - Custom getenv function to find environment variables
 * @name: Name of the variable
 * Return: Pointer to the value, or NULL if not found
 */
char *_getenv(const char *name)
{
	int i = 0;
	int len = strlen(name);

	while (environ[i])
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}
	return (NULL);
}

/**
 * check_current_dir - Checks if command exists in current directory
 * @command: The command name
 * Return: Full path if found, or NULL
 */
char *check_current_dir(char *command)
{
	struct stat st;

	if (stat(command, &st) == 0)
		return (strdup(command));
	return (NULL);
}

/**
 * find_path - Searches for a command in the PATH directories
 * @command: The command name
 * Return: Full path of the command if found, or NULL if not found
 */
char *find_path(char *command)
{
	char *path_env, *path_copy, *token, *file_path;
	struct stat st;
	int cmd_len, dir_len;

	if (command[0] == '/' || command[0] == '.')
		return (check_current_dir(command));

	path_env = _getenv("PATH");
	if (!path_env || strlen(path_env) == 0)
		return (check_current_dir(command));

	path_copy = strdup(path_env);
	cmd_len = strlen(command);
	token = strtok(path_copy, ":");

	while (token != NULL)
	{
		dir_len = strlen(token);
		file_path = malloc(dir_len + cmd_len + 2);
		if (!file_path)
		{
			free(path_copy);
			return (NULL);
		}
		strcpy(file_path, token);
		strcat(file_path, "/");
		strcat(file_path, command);

		if (stat(file_path, &st) == 0)
		{
			free(path_copy);
			return (file_path);
		}
		free(file_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (check_current_dir(command));
}
