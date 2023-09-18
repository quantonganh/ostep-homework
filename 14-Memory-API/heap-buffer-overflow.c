#include "stdio.h"
#include "stdlib.h"

int main() {
    int size = 100;
    int *a = malloc(size * sizeof(int));
    if (a == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    a[100] = 0;
    printf("a[100]: %d\n", a[100]);

    return 0;
}