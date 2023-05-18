//
// Created by Quan Tong on 18/05/2023.
//
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork failed\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("Child process: before closing STDOUT_FILENO\n");
        close(STDOUT_FILENO);
        printf("Child process: after closing STDOUT_FILENO\n");
    } else {
        wait(NULL);
        printf("Parent process: child process completed\n");
    }
}
