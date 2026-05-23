#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

extern char **environ;

/* Custom Safe Memory and String Helpers */
size_t _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
char *_strtok(char *str, const char *delim);
int _atoi(char *s);

/* Core Logic and Main Handlers */
int main(int ac, char **av);
void handle_sigint(int sig);
int execute_logical(char *line, char *shell_name, int status);
int execute_command(char **args, char *shell_name, char *line, int status);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/* Parsing and Path Resolution */
char *find_path(char *command);
char *_getenv(const char *name);

/* Built-in Operations */
int check_builtins(char **args, int status, char *shell_name, char *line);
void print_env(void);
int _setenv(const char *variable, const char *value);
int _unsetenv(const char *variable);
#endif /* SHELL_H */
