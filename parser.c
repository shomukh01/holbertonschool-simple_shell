#include "shell.h"

/**
 * tokenize_input - Splits an input line into an array of tokens
 * @line: The input string to parse
 *
 * Return: A null-terminated array of tokens, or NULL on allocation failure
 */
char **tokenize_input(char *line)
{
	int buf_size = 64;
	int position = 0;
	char **tokens = malloc(buf_size * sizeof(char *));
	char *token;
	int old_size;

	if (!tokens)
		return (NULL);

	/* Replaced standard strtok with custom _strtok to comply with rules */
	token = _strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= buf_size)
		{
			old_size = buf_size;
			buf_size += 64;
			/* Replaced standard realloc with custom safe _realloc */
			tokens = _realloc(tokens, old_size * sizeof(char *), buf_size * sizeof(char *));
			if (!tokens)
				return (NULL);
		}

		token = _strtok(NULL, " \t\r\n\a");
	}
	tokens[position] = NULL;
	return (tokens);
}
