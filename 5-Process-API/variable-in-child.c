//
// Created by Quan Tong on 17/05/2023.
//
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main(void) {
    int x = 100;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(EXIT_FAILURE);
    } else if (rc == 0) {
        x += 1;
        printf("Child process - x: %d\n", x);
    } else {
        x -= 1;
        printf("Parent process - x: %d\n", x);
        wait(NULL);
    }
    return 0;
}
