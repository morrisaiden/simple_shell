#ifndef ALIAS_BUILTIN_H
#define ALIAS_BUILTIN_H
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Alias {
    char *name;
    char *value;
    struct Alias *next;
} Alias;

void add_alias(const char *name, const char *value);
void list_aliases();
void execute_alias_builtin(char **argv);

#endif
