//
// Created by Quan Tong on 19/05/2023.
//
#include "stdio.h"
#include "time.h"
#include "unistd.h"

#define SECOND 1000000000L

long long get_nanosec(struct timespec t1, struct timespec t2) {
    return (t2.tv_sec - t1.tv_sec) * SECOND + t2.tv_nsec - t1.tv_nsec;
}

int main() {
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    printf("start: %d seconds, %d nanoseconds\n", start.tv_sec, start.tv_nsec);

    int N = 1000000;
    for (int i = 0; i < N; i++) {
        read(0, NULL, 0);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("end: %d seconds, %d nanoseconds\n", end.tv_sec, end.tv_nsec);

    long elapsed = get_nanosec(start, end);
    printf("The cost of a 0-byte read system call: %d nanoseconds\n", elapsed / N);
}
