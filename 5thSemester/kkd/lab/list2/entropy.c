#include <stdio.h>
#include <math.h>

#include "entropy.h"

double entropy(char* filename) {
    FILE* file = fopen(filename, "r");

    unsigned int counts[256];
    unsigned int length = 0;

    for (int i = 0; i < 256; counts[i++] = 0);

    int c;

    while ((c = getc(file)) != EOF) {
        counts[c]++;
        length++;
    }

    double probabilities[256];

    for (int i = 0; i < 256; i++) {
        probabilities[i] = (double)counts[i] / length;
    }

    double entropy = 0;

    for (int i = 0; i < 256; i++) {
        if (probabilities[i]) {
            entropy -= probabilities[i] * log2(probabilities[i]);
        }
    }
        
    fclose(file);
    return entropy;
}
