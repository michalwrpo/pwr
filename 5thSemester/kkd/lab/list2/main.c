#include <stdio.h>
#include <string.h>

#include "arithmetic.h"

int main(int argc, char** argv) {
    if (argc != 3 && argc != 4) {
        fprintf(stderr, "Usage: %s [input] [output] [-d]", argv[0]);
        return 1;
    }

    if (argc == 4 && strcmp(argv[3], "-d")) {
        decode(argv[1], argv[2]);
        printf("Decoded successfully.\n");
    } else {
        encode(argv[1], argv[2]);
        printf("Encoded successfully.\n");
    }

    return 0;
}