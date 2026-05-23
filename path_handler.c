#include "shell.h"

/**
 * _getenv - Custom getenv function to retrieve environment variables
 * @name: Name of the variable to search for
 *
 * Return: Pointer to the variable value, or NULL if not found
 */
char *_getenv(const char *name)
{
	int i = 0;
	size_t len = _strlen(name);

	while (environ[i])
	{
		if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}
	return (NULL);
}

/**
 * find_path - Resolves the full path of a command using PATH variable
 * @command: The command name to search for
 *
 * Return: Full path of the command, or NULL if not found
 */
char *find_path(char *command)
{
	char *path_env = _getenv("PATH");
	char *path_copy, *token, *full_path;
	struct stat st;

	if (command && (command[0] == '/' || command[0] == '.'))
	{
		if (stat(command, &st) == 0)
			return (command);
	}

	if (!path_env || _strlen(path_env) == 0)
		return (NULL);

	/* Safe duplication because standard strdup is allowed here */
	path_copy = malloc(_strlen(path_env) + 1);
	if (!path_copy)
		return (NULL);
	
	{
		size_t i;
		for (i = 0; path_env[i] != '\0'; i++)
			path_copy[i] = path_env[i];
		path_copy[i] = '\0';
	}

	/* Replaced standard strtok with custom _strtok */
	token = _strtok(path_copy, ":");

	while (token)
	{
		full_path = malloc(_strlen(token) + _strlen(command) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		
		{
			size_t i, j = 0;
			for (i = 0; token[i] != '\0'; i++)
				full_path[j++] = token[i];
			full_path[j++] = '/';
			for (i = 0; command[i] != '\0'; i++)
				full_path[j++] = command[i];
			full_path[j] = '\0';
		}

		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		token = _strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
