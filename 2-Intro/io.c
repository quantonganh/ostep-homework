//
// Created by Quan Tong on 15/05/2023.
//
#include "unistd.h"
#include "assert.h"
#include "fcntl.h"

int main() {
    int fd = open("/tmp/file", O_WRONLY | O_CREAT | O_TRUNC | S_IRWXU);
    assert(fd > -1);
    int rc = write(fd, "hello world\n", 13);
    assert(rc == 13);
    close(fd);
    return 0;
}
