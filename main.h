#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void execmd(char **argv);
int is_env_command(const char *command);
char *custom_getline(char **lineptr, size_t *n);
void execute_env_builtin();
char *get_location(char *command);
void execute_exit_builtin(char **argv);
char *get_location(char *command);
void execute_exit_builtin(char **argv);
void execute_setenv_builtin(char **argv);
void execute_commands_from_file(const char *filename);
void execute_unsetenv_builtin(char **argv);
void execute_cd_builtin(char **argv);
void execute_command(char *command);
void execute_exit_builtin1(char **argv);

#endif

