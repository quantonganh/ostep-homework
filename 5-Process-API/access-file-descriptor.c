//
// Created by Quan Tong on 17/05/2023.
//
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "fcntl.h"
#include "string.h"
#include "assert.h"

int main(void) {
    int fd = open("/tmp/file", O_CREAT | O_WRONLY | O_TRUNC | S_IRWXU, 0644);
    int rc = fork();
    char cb[] = "from child\n";
    char pb[] = "from parent\n";
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(EXIT_FAILURE);
    } else if (rc == 0) {
        printf("writing from the child\n");
        int child = write(fd, cb, strlen(cb));
        assert(child == strlen(cb));
    } else {
        printf("writing from the parent\n");
        int parent = write(fd, pb, strlen(pb));
        assert(parent == strlen(pb));
        wait(NULL);
    }
    close(fd);
    return 0;
}