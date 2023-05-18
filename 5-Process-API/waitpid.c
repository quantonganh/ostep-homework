//
// Created by Quan Tong on 18/05/2023.
//
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "time.h"

int main() {
    pid_t pid;
    if ((pid = fork()) == 0) {
        sleep(5);
        exit(EXIT_SUCCESS);
    } else {
        while (1) {
            int status;
            time_t t;
            pid_t result = waitpid(pid, &status, WNOHANG);
            if (result == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            } else if (result == 0) {
                time(&t);
                printf("child process is still running at %s", ctime(&t));
                sleep(1);
            } else {
                printf("child process finished.\n");
                break;
            }
        }
    }
}