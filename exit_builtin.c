#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void execute_exit_builtin1(char **argv) {
	int status;
    if (argv[1] == NULL) {
        exit(0);
    }


    status = atoi(argv[1]);
    exit(status);
}

