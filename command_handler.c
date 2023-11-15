#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/**
 * execute_command - Executes a command using execve
 * @command: The command to be executed
 */
void execute_command(char *command) {
    char *token;
    char *buf = command;
    int i = 0;
    char **array;

    token = strtok(buf, "\t\n");
    array = malloc(sizeof(char *) * 1024);

    while (token) {
        array[i] = token;
        token = strtok(NULL, "\t\n");
        i++;
    }
    array[i] = NULL;

    if (execve(array[0], array, NULL) == -1) {
        perror("Error with the Exec");
        exit(EXIT_FAILURE);
    }

    free(array);
}
