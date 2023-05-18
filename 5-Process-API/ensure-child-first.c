//
// Created by Quan Tong on 18/05/2023.
//
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"

int main() {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork failed\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        close(fd[0]);
        printf("hello\n");
        write(fd[1], "signal", sizeof("signal"));
    } else {
        close(fd[1]);
        char signal[10];
        read(fd[0], signal, sizeof(signal));
        printf("goodbye\n");
    }

    return 0;
}
