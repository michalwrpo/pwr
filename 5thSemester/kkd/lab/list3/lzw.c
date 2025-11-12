#include <stdio.h>
#include <stdlib.h>

#include "elias.h"
#include "fibonacci_coding.h"

#include "lzw.h"

#define DIFF_BYTES 256

typedef struct {
    int prefix_index;
    unsigned char last;
} word;

void lzw_encode(char* inputFilename, char* outputFilename, unsigned int coding) {
    unsigned int maxSeqLen = 64, seqLen = 0, dirLen, i = 0;
    unsigned int* seq = malloc(maxSeqLen * sizeof(unsigned int));
    int ch, cur = -1;
    unsigned char c, ended;

    word* dir = malloc((DIFF_BYTES + maxSeqLen) * sizeof(word));

    for (dirLen = 0; dirLen < DIFF_BYTES; dirLen++) {
        dir[dirLen].last = dirLen;
        dir[dirLen].prefix_index = -1;
    }
    
    FILE* infile = fopen(inputFilename, "r");

    while ((ch = fgetc(infile)) != EOF) {        
        c = ch;
        ended = 1;

        while (i < dirLen) {
            if (dir[i].last == c && dir[i].prefix_index == cur) {
                cur = i;
                ended = 0;
                i++;
                break;
            }
            i++;
        }
        
        if (ended) {
            word newWord;
            newWord.last = c;
            newWord.prefix_index = cur;
    
            seq[seqLen++] = cur;
            dir[dirLen++] = newWord;
    
            if (seqLen == maxSeqLen) {
                maxSeqLen *= 2;
                seq = realloc(seq, maxSeqLen * sizeof(unsigned int));
                dir = realloc(dir, (DIFF_BYTES + maxSeqLen) * sizeof(word));
            }
            
            cur = -1;
            i = 0;

            while (i < dirLen) {
                if (dir[i].last == c && dir[i].prefix_index == cur) {
                    cur = i;
                    ended = 0;
                    i++;
                    break;
                }
                i++;
            }
        }
    }
    
    if (cur != -1) {
        seq[seqLen++] = cur;
    }        

    if (coding == 0) {
        omega_encode(seq, seqLen, outputFilename);
    } else if (coding == 1) {
        delta_encode(seq, seqLen, outputFilename);
    } else if (coding == 2) {
        gamma_encode(seq, seqLen, outputFilename);
    } else {
        fibonacci_encode(seq, seqLen, outputFilename);
    }

    free(seq);
    free(dir);

    fclose(infile);
}

int lzw_decode(char* inputFilename, char* outputFilename, unsigned int coding) {
    unsigned int seqLen, maxDirLen = 64, maxStackLen = 64, i, j, dirLen, prev = -1;
    unsigned int* seq;
    unsigned char* stack = malloc(maxStackLen * sizeof(char));
    unsigned char first = 1;

    word w;
    word* dir = malloc((DIFF_BYTES + maxDirLen) * sizeof(word));

    for (dirLen = 0; dirLen < DIFF_BYTES; dirLen++) {
        dir[dirLen].last = dirLen;
        dir[dirLen].prefix_index = -1;
    }

    if (coding == 0) {
        omega_decode(inputFilename, &seq, &seqLen);
    } else if (coding == 1) {
        delta_decode(inputFilename, &seq, &seqLen);
    } else if (coding == 2) {
        gamma_decode(inputFilename, &seq, &seqLen);
    } else {
        fibonacci_decode(inputFilename, &seq, &seqLen);
    }

    FILE* outfile = fopen(outputFilename, "w");
    if (!outfile) {
        fprintf(stderr, "Failed to open output file");
        free(stack);
        free(dir);
        free(seq);
        return 2;
    }

    for (i = 0; i < seqLen; i++) {
        if (seq[i] > dirLen) {
            fprintf(stderr, "Incorrect encoding in input file.\n");
            return 1;
        }

        if (!first) {
            word newWord;
            newWord.prefix_index = prev;
    
            if (seq[i] == dirLen) {
                w = dir[prev];
            } else {
                w = dir[seq[i]];    
            }
    
            while (w.prefix_index > -1) {
                w = dir[w.prefix_index];
            }
    
            newWord.last = w.last;
            
            dir[dirLen++] = newWord;

            if (dirLen == DIFF_BYTES + maxDirLen) {
                maxDirLen *= 2;
                dir = realloc(dir, (DIFF_BYTES + maxDirLen) * sizeof(word));
            }
        } else {
            first = 0;
        }
        
        w = dir[seq[i]];

        j = 0;
        while (w.prefix_index > -1) {
            stack[j++] = w.last;
            w = dir[w.prefix_index];

            if (j == maxStackLen) {
                maxStackLen *= 2;
                stack = realloc(stack, maxStackLen * sizeof(char));
            }
        }
        stack[j++] = w.last;

        while (j-- > 0) {
            fputc(stack[j], outfile);
        }

        prev = seq[i];
    }

    fclose(outfile);

    free(seq);
    free(dir);
    free(stack);

    return 0;
}

