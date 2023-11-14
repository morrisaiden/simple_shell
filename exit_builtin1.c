#include "main.h"
#include <stdio.h>
#include <stdlib.h>

void execute_exit_builtin(char **argv) {
    if (argv[1] == NULL) {
        // No status argument provided, exit with status 0.
        exit(0);
    }

    int status = atoi(argv[1]);
    exit(status);
}

