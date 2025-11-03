#include <stdio.h>
#include <string.h>

#include "arithmetic.h"
#include "entropy.h"

int main(int argc, char** argv) {
    if (argc != 3 && argc != 4) {
        fprintf(stderr, "Usage: %s [input] [output] [-d]", argv[0]);
        return 1;
    }

    if (argc == 4 && (strcmp(argv[3], "-d") == 0)) {
        decode(argv[1], argv[2]);
        printf("Decoded successfully.\n");
        return 0;
    } 
    
    encode(argv[1], argv[2]);
    printf("Encoded successfully.\n");
    
    FILE* in_file = fopen(argv[1], "r");
    FILE* out_file = fopen(argv[2], "r");

    unsigned in_len = 0, out_len = 0;
    int c;

    while ((c = getc(in_file)) != EOF) {
        in_len++;
    }

    while ((c = getc(out_file)) != EOF) {
        out_len++;
    }

    double percent = 100 * (double)out_len / in_len;
    double avglen = (double)out_len / in_len * 8;
    
    double entr = entropy(argv[1]);
    printf("Input entropy: %f\n", entr);
    printf("Average symbol length: %f\n", avglen);

    printf("Input length (in bytes): %u\n", in_len);
    printf("Output length (in bytes): %u (%.2f%%)\n", out_len, percent);


    fclose(in_file);
    fclose(out_file);

    return 0;
}