#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

void display_prompt() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        fprintf(stderr, "minishell:%s:%s$ ", getenv("USER"), cwd);
    } else {
        fprintf(stderr, "minishell:???:???$ ");
    }
}

void execute_command(char *args[], int background) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return;
    } else if (pid == 0) { 
        if (execvp(args[0], args) < 0) {
            fprintf(stderr, "minishell:%s: %s\n", args[0], strerror(errno));
            exit(EXIT_FAILURE);
        }
    } else { 
        if (!background) {
            int status;
            waitpid(pid, &status, 0);
        }
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];
    int background;

    while (1) {
        display_prompt();
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break; 
        }
        command[strcspn(command, "\n")] = '\0';
        char *token = strtok(command, " \t");
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " \t");
        }
        args[i] = NULL;
        if (i == 0) {
            continue;
        }
        if (strcmp(args[i - 1], "&") == 0) {
            background = 1;
            args[i - 1] = NULL;
            i--;
        } else {
            background = 0;
        }
        if (strcmp(args[0], "exit") == 0) {
            if (i > 1 || background) {
                fprintf(stderr, "minishell:%s: Too many arguments for exit\n", args[0]);
            } else {
                break;
            }
        } else if (strcmp(args[0], "cd") == 0) {
            if (i > 2) {
                fprintf(stderr, "minishell:%s: Too many arguments for cd\n", args[0]);
            } else if (i == 1) {
                chdir(getenv("HOME"));
            } else {
                if (strcmp(args[1], "~") == 0) {
                    chdir(getenv("HOME"));
                } else {
                    if (chdir(args[1]) != 0) {
                        perror("chdir");
                    }
                }
            }
        } else {
            execute_command(args, background);
        }

        int status;
        pid_t pid;
        while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
            fprintf(stderr, "pid %d done\n", pid);
        }
    }

    return 0;
}

