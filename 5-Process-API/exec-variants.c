//
// Created by Quan Tong on 18/05/2023.
//
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "assert.h"

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        char *execv_args[] = {"/bin/ls", NULL};
        if (execv(execv_args[0], execv_args) == -1) {
            perror("execv");
            exit(EXIT_FAILURE);
        };
    } else {
        int execv_wait = wait(NULL);
        assert(execv_wait >= 0);
    }

    if ((fork()) == 0) {
        char *execvp_args[] = {"ls", NULL};
        if (execvp(execvp_args[0], execvp_args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        };
    } else {
        int execvp_wait = wait(NULL);
        assert(execvp_wait >= 0);
    }

    if ((fork()) == 0) {
        if (execl("/bin/ls", "ls", NULL) == -1) {
            perror("execl");
            exit(EXIT_FAILURE);
        };
    } else {
        int execl_wait = wait(NULL);
        assert(execl_wait >= 0);
    }

    return 0;
}