# Simple Shell

## Description
Simple Shell is a basic UNIX command line interpreter written in C.
It reads a command from standard input, creates a child process, and executes the command using execve.

## Requirements
- Ubuntu 20.04 LTS
- gcc
- Betty style
- No memory leaks
- No more than 5 functions per file

## Compilation
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## Usage
./hsh

Example:
#cisfun$ /bin/ls
#cisfun$

Non-interactive mode:
echo "/bin/ls" | ./hsh

## Files
- README.md: project documentation
- AUTHORS: list of contributors
- man_1_simple_shell: manual page
- main.c: shell entry point
- shell.h: header file
- execute.c: command execution

## Authors
Shomukh Aldosari & Mohammed Aldawsari