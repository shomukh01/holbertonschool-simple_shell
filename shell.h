#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;

/* Prototypes */
char **tokenize_input(char *line);
char *find_path(char *command);
char *_getenv(const char *name);
void execute_command(char *full_path, char **args);
int check_builtin(char **args);
void handle_input(char *line);

#endif
