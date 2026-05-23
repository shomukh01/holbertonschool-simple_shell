#include "shell.h"

/**
 * main - Entry point for the simple shell program
 * @ac: Argument count
 * @av: Argument vector (contains shell name at av[0])
 *
 * Return: 0 on success, or status code on exit
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t bytes_read;
	int status = 0;
	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		bytes_read = getline(&line, &len, stdin);
		if (bytes_read == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			free_env_vars(); /* Crucial: cleans the 13 bytes on Ctrl+D */
			exit(status);
		}

		/* [قواطع التفكيك والتنفيذ العادية الخاصة بالشل الخاص بك توضع هنا] */
		/* مثال الاستدعاء عند معالجة المصفوفة المقطعة args: */
		/* status = check_builtins(args, status, av[0], line); */
	}
	return (status);
}
