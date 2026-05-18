#include "shell.h"

/**
 * tokenize_input - Splits a string into an array of tokens
 * @line: The input string to tokenize
 * Return: Array of pointers to tokens, or NULL on failure
 */
char **tokenize_input(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("Allocation error");
		return (NULL);
	}

	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("Reallocation error");
				return (NULL);
			}
		}
		token = strtok(NULL, " \t\r\n\a");
	}
	tokens[position] = NULL;
	return (tokens);
}
