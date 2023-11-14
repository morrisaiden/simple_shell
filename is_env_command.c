#include <stdio.h>
#include <string.h>

int is_env_command(const char *command) {
    return (strcmp(command, "env") == 0);
}

