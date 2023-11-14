#ifndef ALIAS_BUILTIN_H
#define ALIAS_BUILTIN_H

#include "main.h"

typedef struct Alias {
    char *name;
    char *value;
    struct Alias *next;
} Alias;

extern Alias *alias_list;

void add_alias(const char *name, const char *value);
void list_aliases();
void execute_alias_builtin(char **argv);

#endif

