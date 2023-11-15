#include "main.h"
#include <stdio.h>
#include <stdlib.h>

void execute_exit_builtin(char **argv) {
    int status;
    if (argv[1] == NULL)
    {
        exit(0);
    }

    status = atoi(argv[1]);
    exit(status);
}

