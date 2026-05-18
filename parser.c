#include "shell.h"

/**
 * tokenize_input - Splits a string into an array of tokens
 * @line: The input string from getline
 * Return: Array of pointers to the tokens, or NULL on failure
 */
char **tokenize_input(char *line)
{
	char **tokens = NULL;
	char *token = NULL;
	int i = 0;

	tokens = malloc(sizeof(char *) * 64);
	if (!tokens)
	{
		perror("Allocation error");
		return (NULL);
	}

	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, " \t\r\n\a");
	}
	tokens[i] = NULL;

	return (tokens);
}
