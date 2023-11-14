#include <stdio.h>
#include <stdlib.h>

ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream) {
    if (lineptr == NULL || n == NULL) {
        return -1;
    }

    size_t bufsize = 128;
    ssize_t bytesRead = 0;
    int nextChar;

    if (*lineptr == NULL) {
        *lineptr = (char *)malloc(bufsize);
        if (*lineptr == NULL) {
            return -1;
        }
        *n = bufsize;
    }

    char *line = *lineptr;

    while (1) {
        nextChar = fgetc(stream);

        if (nextChar == EOF || nextChar == '\n') {
            line[bytesRead] = '\0';
            return bytesRead;
        }

        line[bytesRead] = (char)nextChar;
        bytesRead++;

        if (bytesRead >= bufsize - 1) {
            bufsize *= 2;
            char *newLine = (char *)realloc(line, bufsize);

            if (newLine == NULL) {
                free(line);
                *lineptr = NULL;
                return -1;
            }

            line = newLine;
            *lineptr = line;
            *n = bufsize;
        }
    }
}

int main() {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    printf("Enter some text (Ctrl+D to end):\n");

    while ((read = custom_getline(&line, &len, stdin)) != -1) {
        printf("Read %zd characters: %s\n", read, line);
    }

    free(line);

    return 0;
}

