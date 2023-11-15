#include "main.h"
#include <stdio.h>
#include <stdlib.h>

void execute_unsetenv_builtin(char **argv) {
    if (argv[1] == NULL || argv[2] != NULL) {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
        return;
    }

    if (unsetenv(argv[1]) == -1) {
        perror("unsetenv failed");
    }
}
