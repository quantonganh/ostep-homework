//
// Created by Quan Tong on 15/05/2023.
//
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "common.h"

int main() {
    int *p = malloc(sizeof(int));
    assert(p != NULL);
    printf("(%d) address pointed to by p: %p\n", getpid(), p);

    *p = 0;
    while (1) {
        Spin(1);
        *p += 1;
        printf("(%d) p: %d\n", getpid(), *p);
    }
}