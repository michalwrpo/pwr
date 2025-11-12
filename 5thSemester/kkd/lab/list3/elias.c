#include <stdio.h>
#include <stdlib.h>

#include "elias.h"

typedef struct {
    unsigned char arr[90];
    signed char top;
} stack;

void push(stack* s, unsigned char v) {
    s->arr[++s->top] = v;
}

unsigned char pop(stack* s) {
    if (s->top == -1)
        return 2;
    
    unsigned char v = s->arr[s->top];
    s->top--;
    return v;
}

void gamma_encode(unsigned int* sequence, unsigned int sequenceLength, char* outputFilename) {
    FILE* file = fopen(outputFilename, "w");

    unsigned int num, i, j, k, len = 0;
    unsigned char c = 0;

    for (i = 0; i < sequenceLength; i++) {
        num = sequence[i] + 1;

        j = 0;
        while (num >> ++j);
        
        for (k = 0; k < j - 1; k++) {
            c <<= 1;
            len++;

            if (len == 8) {
                fputc(c, file);
                len = 0;
                c = 0;
            }
        }

        for (k = 0; k < j; k++) {
            c = c << 1 | ((num >> (j - k - 1)) & 1);
            len++;

            if (len == 8) {
                fputc(c, file);
                len = 0;
                c = 0;
            }
        }
    }

    if (len) {
        c <<= (8 - len);
        fputc(c, file);
    }
    
    fclose(file);
}

void gamma_decode(char* inputFilename, unsigned int** sequence, unsigned int* sequenceLength) {
    FILE* file = fopen(inputFilename, "r");

    unsigned int num, i = 0, maxSeqLen = 100;
    int ch;
    unsigned char c, remaining, zeros = 1;

    *sequence = malloc(maxSeqLen * sizeof(unsigned int));

    while ((ch = getc(file)) != EOF) {
        c = ch;
        remaining = 8;
        
        while (remaining--) {
            if (zeros) {
                if (!(c & 0x80)) {
                    i++;
                    c <<= 1;
                    continue;
                }

                if (!i) {
                    (*sequence)[(*sequenceLength)++] = 0;
                    c <<= 1;
                    continue; 
                }
                
                zeros = 0;
                num = 1;
            } else {
                i--;
                num = (num << 1) | ((c & 0x80) >> 7); 

                
                if (!i) {
                    (*sequence)[(*sequenceLength)++] = num - 1;
                    zeros = 1;
                }
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


void delta_encode(unsigned int* sequence, unsigned int sequenceLength, char* outputFilename) {
    FILE* file = fopen(outputFilename, "w");

    unsigned int num, num_len, i, j, k, len = 0;
    unsigned char c = 0;

    for (i = 0; i < sequenceLength; i++) {
        num = sequence[i] + 1;

        num_len = 0;
        while (num >> ++num_len);

        j = 0;
        while (num_len >> ++j);
        
        for (k = 0; k < j - 1; k++) {
            c <<= 1;
            len++;

            if (len == 8) {
                fputc(c, file);
                len = 0;
                c = 0;
            }
        }

        for (k = 0; k < j; k++) {
            c = c << 1 | ((num_len >> (j - k - 1)) & 1);
            len++;

            if (len == 8) {
                fputc(c, file);
                len = 0;
                c = 0;
            }
        }

        for (k = 1; k < num_len; k++) {
            c = c << 1 | ((num >> (num_len - k - 1)) & 1);
            len++;

            if (len == 8) {
                fputc(c, file);
                len = 0;
                c = 0;
            }
        }
    }

    if (len) {
        c <<= (8 - len);
        fputc(c, file);
    }
    
    fclose(file);
}

void delta_decode(char* inputFilename, unsigned int** sequence, unsigned int* sequenceLength) {
    FILE* file = fopen(inputFilename, "r");

    unsigned int num, numLen, i = 0, maxSeqLen = 100;
    int ch;
    unsigned char c, remaining, step = 0;

    *sequence = malloc(maxSeqLen * sizeof(unsigned int));

    while ((ch = getc(file)) != EOF) {
        c = ch;
        remaining = 8;
        
        while (remaining--) {
            if (step == 0) {
                if (!(c & 0x80)) {
                    i++;
                    c <<= 1;
                    continue;
                }

                if (!i) {
                    (*sequence)[(*sequenceLength)++] = 0;
                    c <<= 1;
                    continue; 
                }
                
                step = 1;
                numLen = 1;
            } else if (step == 1) {
                i--;
                numLen = (numLen << 1) | ((c & 0x80) >> 7); 

                if (!i) {
                    step = 2;
                    num = 1;
                    numLen--;
                }
            } else {
                numLen--;
                num = (num << 1) | ((c & 0x80) >> 7);

                if (!numLen) {
                    (*sequence)[(*sequenceLength)++] = num - 1;
                    step = 0;
                }
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


void omega_encode(unsigned int* sequence, unsigned int sequenceLength, char* outputFilename) {
    FILE* file = fopen(outputFilename, "w");

    unsigned int num, num_len, i, len = 0;
    unsigned char bit, c = 0;
    stack s;
    s.top = -1;
    
    for (i = 0; i < sequenceLength; i++) {
        num = sequence[i] + 1;
        push(&s, 0);

        while(num > 1) {
            num_len = 0;

            while (num) {
                bit = num & 1;
                push(&s, bit);

                num_len++;
                num >>= 1;
            }

            num = num_len - 1;
        }

        bit = pop(&s);
        while (bit < 2) {
            c = (c << 1) | bit;
            len++;
            
            if (len == 8) {
                fputc(c, file);
                len = 0;
                c = 0;
            }

            bit = pop(&s);
        }
    }

    if (len) {
        while (len++ < 8)
            c = (c << 1) | 1;
        
        fputc(c, file);
    }
    
    fclose(file);
}

void omega_decode(char* inputFilename, unsigned int** sequence, unsigned int* sequenceLength) {
    FILE* file = fopen(inputFilename, "r");

    unsigned int num = 1, i = 0, maxSeqLen = 100;
    int ch;
    unsigned char c, remaining;

    *sequence = malloc(maxSeqLen * sizeof(unsigned int));

    while ((ch = getc(file)) != EOF) {
        c = ch;
        remaining = 8;
        
        while (remaining--) {
            if (!i) {
                if (c & 0x80) {
                    i = num;
                    num = 1;
                } else {
                    (*sequence)[(*sequenceLength)++] = num - 1;
                    num = 1;
                }
            } else {
                i--;
                num = (num << 1) | ((c & 0x80) >> 7); 
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
