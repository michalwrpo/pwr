#include <stdio.h>
#include <stdlib.h>

#include "fibonacci_coding.h"

#define FIB_UINTS 46

void fibonacci_encode(unsigned int* sequence, unsigned int sequenceLength, char* outputFilename) {
    FILE* file = fopen(outputFilename, "w");

    unsigned int num, numLen, i, j, len = 0;
    unsigned char c = 0;
    unsigned int fibonacci[FIB_UINTS];
    unsigned char coefs[FIB_UINTS];

    fibonacci[0] = 1;
    fibonacci[1] = 2;

    for (i = 2; i < FIB_UINTS; i++) {
        fibonacci[i] = fibonacci[i-1] + fibonacci[i-2];
    }

    for (i = 0; i < sequenceLength; i++) {
        num = sequence[i] + 1;

        for (j = 0; j < FIB_UINTS; j++) {
            coefs[j] = 0;
        }        

        numLen = 1;
        while(num - fibonacci[numLen - 1] >= fibonacci[numLen]) {
            numLen++;
        }

        if (num == 1) {
            numLen = 0;
        }
        
        j = numLen;
        while(num) {
            if (num >= fibonacci[j]) {
                coefs[j] = 1;
                num -= fibonacci[j];
            }
            j--;
        }

        for (j = 0; j < numLen + 1; j++) {
            c = (c << 1) | coefs[j];
            len++;

            if (len == 8) {
                fputc(c, file);
                len = 0;
                c = 0;
            }
        }

        c = (c << 1) | 1;
        len++;

        if (len == 8) {
            fputc(c, file);
            len = 0;
            c = 0;
        }        
    }

    if (len) {
        c <<= (8 - len);
        fputc(c, file);
    }
    
    fclose(file);
}

void fibonacci_decode(char* inputFilename, unsigned int** sequence, unsigned int* sequenceLength) {
    FILE* file = fopen(inputFilename, "r");

    unsigned int num = 0, i = 0, maxSeqLen = 100;
    int ch;
    unsigned char c, remaining, bit, prev = 0;
    unsigned int fibonacci[FIB_UINTS];

    fibonacci[0] = 1;
    fibonacci[1] = 2;

    for (i = 2; i < FIB_UINTS; i++) {
        fibonacci[i] = fibonacci[i-1] + fibonacci[i-2];
    }

    *sequence = malloc(maxSeqLen * sizeof(unsigned int));

    i = 0;

    while ((ch = getc(file)) != EOF) {
        c = ch;
        remaining = 8;
        
        while (remaining--) {
            bit = (c & 0x80) >> 7;

            if (prev == 1 && bit == 1) {
                (*sequence)[(*sequenceLength)++] = num - 1;

                i = 0;
                prev = 0;
                num = 0;
            } else {
                num += bit * fibonacci[i++];
                prev = bit;
            }

            c <<= 1;

            if (*sequenceLength == maxSeqLen) {
                maxSeqLen *= 2;
                (*sequence) = realloc(*sequence, maxSeqLen * sizeof(unsigned int));
            }
        }
    }

    fclose(file);
}
