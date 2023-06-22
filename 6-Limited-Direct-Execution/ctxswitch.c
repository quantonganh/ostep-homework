//
// Created by Quan Tong on 18/05/2023.
//
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "unistd.h"
#include "pthread.h"
#include "mach/thread_policy.h"
#include "mach/thread_act.h"

#define SECOND 1000000000L

void bind_thread_to_core(pthread_t thread, int core_id) {
    thread_affinity_policy_data_t policy;
    policy.affinity_tag = core_id;

    mach_port_t mach_thread = pthread_mach_thread_np(thread);
    if (thread_policy_set(mach_thread, THREAD_AFFINITY_POLICY, (thread_policy_t)&policy, THREAD_AFFINITY_POLICY_COUNT) != KERN_SUCCESS) {
        perror("thread_policy_set");
        exit(EXIT_FAILURE);
    }
}

long long get_nanosec(struct timespec t1, struct timespec t2) {
    return (t2.tv_sec - t1.tv_sec) * SECOND + t2.tv_nsec - t1.tv_nsec;
}

int main() {
    int first_fd[2];
    int second_fd[2];
    if (pipe(first_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (pipe(second_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int N = 1000000;
    int core_id = 0;
    pid_t pid1 = fork();

    struct timespec start, end;
    if (pid1 < 0) {
        fprintf(stderr, "fork failed\n");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        bind_thread_to_core(pthread_self(), core_id);

        for (int i = 0; i < N; i++) {
            write(first_fd[1], NULL, 0);
            read(second_fd[0], NULL, 0);
        }
    } else {
        bind_thread_to_core(pthread_self(), core_id);

        clock_gettime(CLOCK_MONOTONIC, &start);
        printf("start: %d seconds, %d nanoseconds\n", start.tv_sec, start.tv_nsec);
        for (int i = 0; i < N; i++) {
            read(first_fd[0], NULL, 0);
            write(second_fd[1], NULL, 0);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        printf("end: %d seconds, %d nanoseconds\n", end.tv_sec, end.tv_nsec);

        long elapsed = get_nanosec(start, end);
        printf("The cost of a context switch: %d nanoseconds\n", elapsed / N);
    }

    return 0;
}


