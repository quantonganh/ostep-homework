//
// Created by Quan Tong on 18/05/2023.
//
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main() {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid1 = fork();
    if (pid1 < 0) {
        fprintf(stderr, "fork failed\n");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        close(fd[0]);
        // Redirect stdout to the write end of the pipe
        dup2(fd[1], STDOUT_FILENO);
        char *args[] = { "ls", "-l", NULL};
        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        close(fd[1]);
        wait(NULL);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        fprintf(stderr, "fork failed\n");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        close(fd[1]);
        // Redirect stdin to the read end of the pipe
        dup2(fd[0], STDIN_FILENO);

        char *args[] = { "wc", "-l", NULL};
        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        close(fd[0]);
        wait(NULL);
    }

    return 0;
}


