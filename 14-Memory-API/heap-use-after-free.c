#include "stdio.h"
#include "stdlib.h"

int main() {
    int size = 100;
    int *a = malloc(size * sizeof(int));
    if (a == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    free(a);

    printf("a[0]: %d\n", a[0]);

    return 0;
}