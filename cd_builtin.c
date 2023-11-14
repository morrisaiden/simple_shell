#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * execute_cd_builtin - Executes the built-in 'cd' command
 * @argv: The arguments for the command
 */
void execute_cd_builtin(char **argv) {
    char *new_directory;

    if (argv[1] == NULL) {
        /* No argument provided, change to the user's home directory */
        new_directory = getenv("HOME");
        if (new_directory == NULL) {
            fprintf(stderr, "cd: No home directory defined in HOME environment variable\n");
            return;
        }
    } else if (strcmp(argv[1], "-") == 0) {
        /* Handle "cd -" to change to the previous directory */
        new_directory = getenv("OLDPWD");
        if (new_directory == NULL) {
            fprintf(stderr, "cd: OLDPWD not set\n");
            return;
        }
        printf("%s\n", new_directory); /* Print the directory to stdout */
    } else {
        /* Change to the specified directory */
        new_directory = argv[1];
    }

    /* Use chdir to change the current directory */
    if (chdir(new_directory) == -1) {
        perror("cd failed");
    } else {
        /* Update the PWD environment variable */
        char current_directory[1024];
        if (getcwd(current_directory, sizeof(current_directory)) != NULL) {
            setenv("PWD", current_directory, 1);
        } else {
            perror("cd: Error updating PWD");
        }
    }
}

