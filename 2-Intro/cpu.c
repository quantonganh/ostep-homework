//
// Created by Quan Tong on 15/05/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
	    fprintf(stderr, "usage: cpu <string>\n");
	    exit(1);
    }
    char *str = argv[1];

    while (1) {
	    printf("%s\n", str);
	    Spin(1);
    }
}

