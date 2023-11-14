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
    size_t buf_size = 0;
    char *token;
    char *buf = command;
    int status, i = 0;
    char **array;
    pid_t child_pid;

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

/**
 * main - Entry point for the shell program
 * 
 * Return: Always 0
 */
int main() {
    while (1) {
        write(1, "#cisfun$ ", 9);
        size_t buf_size = 0;
        char *buf = NULL;

        getline(&buf, &buf_size, stdin);

        /* Check if the command exists in the PATH before forking */
        if (access(buf, X_OK) == 0) {
            execute_command(buf);
        }

        free(buf);
    }
    return 0;
}

