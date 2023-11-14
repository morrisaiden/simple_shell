#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char *custom_strtok(char *str, const char *delim, char **saveptr) {
    if (str == NULL && *saveptr == NULL) {
        return NULL;
    }

    char *token_start, *token_end;

    if (str != NULL) {
        token_start = str;
    } else {
        token_start = *saveptr;
    }

    token_start += strspn(token_start, delim);

    if (*token_start == '\0') {
        *saveptr = NULL;
        return NULL;
    }

    token_end = token_start + strcspn(token_start, delim);

    if (*token_end != '\0') {
        *token_end = '\0';
        *saveptr = token_end + 1;
    } else {
        *saveptr = NULL;
    }

    return token_start;
}

int main() {
    char str[] = "This,is,a,custom,strtok,function";
    char delim[] = ",";
    char *saveptr = NULL;
    char *token;

    token = custom_strtok(str, delim, &saveptr);
    while (token != NULL) {
        printf("%s\n", token);
        token = custom_strtok(NULL, delim, &saveptr);
    }

    return 0;
}

