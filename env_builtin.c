#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "main.h"

void execute_env_builtin(void)
{
    extern char **environ;
    char **env = environ;
    
    if (environ == NULL) {
        perror("Error getting environment");
    }

    for (; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}
