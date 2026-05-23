#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

extern char **environ;

/* Core Logic and Main Handlers */
int main(int ac, char **av);
void handle_sigint(int sig);
int execute_logical(char *line, char *shell_name);
int execute_command(char **args, char *shell_name);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, size_t old_size, size_t new_size);


/* Custom Safe String Helpers */
size_t _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);


/* Parsing and Path Resolution */
char **parse_line(char *line);
char *find_path(char *command);
char *_getenv(const char *name);

/* Built-in Operations */
int check_builtins(char **args, int status);
void print_env(void);

void remove_comments(char *line);

#endif /* SHELL_H */
