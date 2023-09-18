#include "stdio.h"

int main() {
    int* nullPtr = NULL;

    printf("Dereferencing the null pointer...\n");
    printf("value: %d\n", *nullPtr);
}