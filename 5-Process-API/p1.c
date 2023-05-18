//
// Created by Quan Tong on 15/05/2023.
//
#include "stdio.h"
#include "unistd.h"

int main() {
    printf("hello world (pid: %d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        printf("hello, I am child (pid: %d)\n", (int) getpid());
    } else {
        printf("hello, I am parent of %d (pid: %d)\n", rc, (int) getpid());
    }
    return 0;
}
