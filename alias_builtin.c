#include "alias_builtin.h"

Alias *alias_list = NULL;

void add_alias(const char *name, const char *value){
    Alias *new_alias = malloc(sizeof(Alias));
    new_alias->name = strdup(name);
    new_alias->value = strdup(value);
    new_alias->next = alias_list;
    alias_list = new_alias;
}

void list_aliases(){
    Alias *current_alias = alias_list;
    while (current_alias != NULL) {
        printf("Alias: %s=%s\n", current_alias->name, current_alias->value);
        current_alias = current_alias->next;
    }
}

void execute_alias_builtin(char **argv) {
    char *name;
    char *token;
    char *value;

    if (argv[1] == NULL) {
        fprintf(stderr, "Usage: alias <name>=<value>\n");
        return;
    }

    token = strtok(argv[1], "=");

    if (token == NULL) {
        fprintf(stderr, "Invalid alias format. Use: alias <name>=<value>\n");
        return;
    }

    name = strdup(token);
    token = strtok(NULL, "");

    if (token == NULL) {
        fprintf(stderr, "Invalid alias format. Use: alias <name>=<value>\n");
        free(name);
        return;
    }

    value = strdup(token);

    add_alias(name, value);
}
