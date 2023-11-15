#include "main.h"
#include <sys/wait.h>

/**
 * execute_logical_and - Executes commands with logical AND
 * @cmd_argv: Array of commands
 *
 * Return: Exit status of the second command or an error code
 */
int execute_logical_and(char **cmd_argv) {
    int status1 = 0;
    int status2 = 0;
    pid_t child_pid1, child_pid2;
    char **cmd_argv2;

    child_pid1 = fork();
    if (child_pid1 == -1) {
        perror("Fork failed");
        return -1;
    } else if (child_pid1 == 0) {
        execmd(cmd_argv);
        exit(0);
    } else {
        wait(&status1);
    }

    if (status1 != 0) {
        return status1;
    }
    cmd_argv2 = cmd_argv + 1;
    
    child_pid2 = fork();
    if (child_pid2 == -1) {
        perror("Fork failed");
        return -1;
    } else if (child_pid2 == 0) {
        execmd(cmd_argv2);
        exit(0);
    } else {
        wait(&status2);
    }

    return status2;
}

/**
 * execute_logical_or - Executes commands with logical OR
 * @cmd_argv: Array of commands
 *
 * Return: Exit status of the second command or an error code
 */
int execute_logical_or(char **cmd_argv) {
    int status1 = 0;
    pid_t child_pid2;
    char **cmd_argv2;
    int status2 = 0;

    pid_t child_pid1 = fork();
    if (child_pid1 == -1) {
        perror("Fork failed");
        return -1;
    } else if (child_pid1 == 0) {
        execmd(cmd_argv);
        exit(0);
    } else {
        wait(&status1);
    }

    if (status1 == 0) {
        return status1;
    }
    cmd_argv2 = cmd_argv + 1;

    child_pid2 = fork();
    if (child_pid2 == -1) {
        perror("Fork failed");
        return -1;
    } else if (child_pid2 == 0) {
        execmd(cmd_argv2);
        exit(0);
    } else {
        wait(&status2);
    }

    return status2;
}

