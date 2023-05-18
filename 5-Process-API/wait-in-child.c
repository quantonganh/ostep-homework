//
// Created by Quan Tong on 18/05/2023.
//
#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "unistd.h"
#include "string.h"
#include "assert.h"
#include "errno.h"

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("Child process: my pid is %d\n", getpid());

        int status;
        pid_t result = wait(&status);
        if (result == -1) {
            perror("wait() failed in child process");
            printf("error code: %d\n", errno);
            exit(1);
        }
    } else {
        int status;
        pid_t result = wait(&status);
        if (result == -1) {
            perror("wait failed\n");
            return 1;
        }

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf("Child process terminated with status: %d\n", exit_status);
        }
    }
}