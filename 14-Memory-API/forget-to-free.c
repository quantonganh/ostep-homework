#include "stdio.h"
#include "stdlib.h"

int main() {
    int* x = malloc(sizeof(int));
    if (x == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    *x = 1;
    printf("x: %d\n", *x);

    // free(x);

    return 0;
}