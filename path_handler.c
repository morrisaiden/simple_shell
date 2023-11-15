#include "path_handler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * find_executable - Finds the full path of an executable in the PATH environment
 * @command: The command to find
 *
 * Returns: A dynamically allocated string containing the full path of the executable,
 *          or NULL if not found or on error. The caller is responsible for freeing
 *          the allocated memory.
 */
char *find_executable(const char *command) {
    char *path_copy;
    char *path = getenv("PATH");
    char *token;

    if (path == NULL) {
        return NULL;
    }

    path_copy = strdup(path);

    if (path_copy == NULL) {
        perror("Error duplicating PATH");
        return NULL;
    }

    token = strtok(path_copy, ":");
    while (token != NULL) {
        char *executable = malloc(strlen(token) + strlen(command) + 2);

        if (executable == NULL) {
            perror("Error allocating memory for executable path");
            free(path_copy);
            return NULL;
        }

        sprintf(executable, "%s/%s", token, command);

        if (access(executable, X_OK) == 0) {
            free(path_copy);
            return executable;
        }

        free(executable);
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

