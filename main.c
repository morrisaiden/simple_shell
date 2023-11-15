#include "main.h"
#include <sys/wait.h>
#include "variable_replacement.h"
#include <sys/wait.h>
#include "alias_builtin.h"

char *previous_dir = NULL;

int main(){
    char *prompt = "(morris) $ ";
    char *lineptr = NULL, *lineptr_copy = NULL;
    size_t n = 0;
    char *token, *saveptr;
    ssize_t nchars_read;
    int status = 0;
    char **cmd_argv;

   while (1) {
        write(1, prompt, strlen(prompt));
        nchars_read = getline(&lineptr, &n, stdin);
        if (nchars_read == -1) {
            write(1, "Exiting shell....\n", 18);
            break;
        }
        if (lineptr[0] == '#') {
            continue;
        }
        lineptr_copy = replace_variables(lineptr);

        lineptr_copy = strdup(lineptr);

        if (lineptr_copy == NULL) {
            perror("tsh: memory allocation error");
            break;
        }

        token = strtok_r(lineptr_copy, ";", &saveptr);

        while (token != NULL) {
            char *command = strdup(token);

            if (command != NULL) {
                char *cmd_line = strdup(command);

                if (cmd_line != NULL) {
                    char *cmd_line_copy = strdup(cmd_line);

                    if (cmd_line_copy != NULL) {
                        char *cmd_copy = cmd_line_copy;

                        int num_tokens = 0;
                        char *cmd_token;

                        while ((cmd_token = strsep(&cmd_copy, " \n")) != NULL) {
                            if (strlen(cmd_token) > 0) {
                                num_tokens++;
                            }
                        }
                        cmd_argv = malloc((num_tokens + 1) * sizeof(char *));

                        if (cmd_argv != NULL) {
                            int i = 0;
                            cmd_token = strtok(cmd_line, " \n");

                            while (cmd_token != NULL) {
                                if (strlen(cmd_token) > 0) {
                                    cmd_argv[i] = strdup(cmd_token);
                                    i++;
                                }
                                cmd_token = strtok(NULL, " \n");
                            }
                            cmd_argv[i] = NULL;

                            if (strcmp(cmd_argv[0], "exit") == 0) {
                                execute_exit_builtin(cmd_argv);
                                free(cmd_argv);
                                break;
                            } else if (strcmp(cmd_argv[0], "cd") == 0) {
                                if (cmd_argv[1] != NULL && strcmp(cmd_argv[1], "-") == 0) {
                                    if (previous_dir != NULL) {
                                        cmd_argv[1] = strdup(previous_dir);
                                    } else {
                                        write(2, "cd: no previous directory\n", 27);
                                        free(cmd_argv);
                                        break;
                                    }
                                    
                                }
                                execute_cd_builtin(cmd_argv);

                                if (previous_dir != NULL) {
                                    free(previous_dir);
                                }
                                previous_dir = getcwd(NULL, 0);
                                free(cmd_argv);
                            } else if (strcmp(cmd_argv[0], "alias") == 0) {
                                execute_alias_builtin(cmd_argv);
                            } else {
                                pid_t child_pid = fork();

                                if (child_pid == -1) {
                                    perror("Fork failed");
                                } else if (child_pid == 0) {
                                    execmd(cmd_argv);
                                    free(cmd_argv);
                                    free(cmd_line_copy);
                                    free(cmd_line);
                                    free(command);
                                    exit(0);
                                } else {
                                    wait(&status);
                                    free(cmd_argv);
                                    free(cmd_line_copy);
                                    free(cmd_line);
                                    free(command);
                                }
                            }
                        } else {
                            perror("tsh: memory allocation error");
                        }
                    } else {
                        perror("tsh: memory allocation error");
                    }
                } else {
                    perror("tsh: memory allocation error");
                }

                token = strtok_r(NULL, ";", &saveptr);
            }
            
        }
        free(lineptr_copy);
    }

    free(previous_dir);
    free(lineptr);

    return status;
}

