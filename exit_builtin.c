#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void execute_exit_builtin(char **argv) {
    if (argv[1] == NULL) {
        exit(0);
    }

    /* Move the declaration to the beginning of the function */
    int status;
    /* Convert string to integer */
    status = atoi(argv[1]);
    exit(status);
}

