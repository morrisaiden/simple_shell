#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char *append_string(char *result, char *start, size_t len, const char *replacement);

char *replace_variables(char *line, int status) {
    char *result = NULL;
    char *ptr = line;
    char *start = NULL;

    while (*ptr) {
        if (*ptr == '$') {
            start = ptr;
            ptr++;

            if (*ptr == '?') {
                int exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
                char exit_status_str[10];
                snprintf(exit_status_str, sizeof(exit_status_str), "%d", exit_status);
                result = append_string(result, start, ptr - start, exit_status_str);
            } else if (*ptr == '$') {
                char shell_pid_str[10];
                snprintf(shell_pid_str, sizeof(shell_pid_str), "%d", getpid());
                result = append_string(result, start, ptr - start, shell_pid_str);
            }
        }
        ptr++;
    }

    if (result == NULL) {
        return strdup(line);
    } else {
        free(line);
        return result;
    }
}

char *append_string(char *result, char *start, size_t len, const char *replacement) {
    size_t current_len = result ? strlen(result) : 0;
    size_t new_len = current_len + len + strlen(replacement);
    result = (char *)realloc(result, new_len + 1);

    if (result) {
        memcpy(result + current_len, start, len);
        memcpy(result + current_len + len, replacement, strlen(replacement));
        result[new_len] = '\0';
    } else {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    return result;
}
