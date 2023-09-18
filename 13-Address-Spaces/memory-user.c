#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

void touchArray(int* a, size_t size) {
    for (size_t i = 0; i < size; i++) {
        a[i] = i;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <memory_size_in_MB> [duraction_in_seconds]\n", argv[0]);
        return 1;
    }

    int memoryInMB = atoi(argv[1]);
    size_t size = (size_t)(memoryInMB * 1024 * 1024) / sizeof(int);
    
    int* a = malloc(size * sizeof(int));
    if (a == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Allocate %.2f MB of memory\n", (double)(size * sizeof(int)) / (1024 * 1024));
    
    int duration = -1;
    if (argc >= 3) {
        duration = atoi(argv[2]);
    }

    time_t startTime = time(NULL);
    time_t currentTime = time(NULL);
    while (duration < 0 || (currentTime - startTime) < duration) {
        touchArray(a, size);
        currentTime = time(NULL);
    }

    free(a);

    return 0;
}