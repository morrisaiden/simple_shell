#include "main.h"
#include <unistd.h>
#include <stdlib.h>

void execute_setenv_builtin(char **argv) {
    if (argv[1] == NULL || argv[2] == NULL || argv[3] != NULL) {
        write(2, "Usage: setenv VARIABLE VALUE\n", 29);
        return;
    }

    if (setenv(argv[1], argv[2], 1) == -1) {
        perror("setenv failed");
    }
}
