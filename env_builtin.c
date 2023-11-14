#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "main.h"

void execute_env_builtin(void)
{
    extern char **environ;
    
    if (environ == NULL) {
        perror("Error getting environment");
    }

    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}

