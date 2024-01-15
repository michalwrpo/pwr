//Zadanie 2, decode.c Michał Waluś

#include "funs.h"
#include <stdio.h>
#include <math.h>

int allowed[1296][4];

void create_list(void) {
    for (int i = 0; i < 1296; i++) {
        for (int j = 0; j < 4; j++) {
            allowed[i][j] = i/(int)pow(6, 3-j) - (i/(int)pow(6, 4-j)) * 6 + 1;
        }
    }
}

void interpret(int red, int white, int guess) {
    int array[4];
    for (int i = 0; i < 4; i++) {
        array[i] = (guess/(int)pow(10, 3 - i)) - (guess/(int)pow(10, 4 - i))*10; 
    }
    for (int i = 0; i < 1296; i++) {
        int temporary[4] = {array[0], array[1], array[2], array[3]};
        if (allowed[i][0] != 0) {
            int innerred = 0, innerwhite = 0;
            for (int j = 0; j < 4; j++) {
                if (allowed[i][j] == temporary[j]) {
                    innerred++;
                    temporary[j] = 0;
                }
            }
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 3; k++) {
                    if (allowed[i][j] == temporary[(j + k + 1) % 4]) {
                        innerwhite++;
                        temporary[(j + k + 1) % 4] = 0;
                    }
                }
            }
            //printf("%d.%d%d | ", i, innerred, innerwhite);
            if (innerred != red || innerwhite != white) {
                allowed[i][0] = 0;
            }
        }
    }
}

int guess(int red, int white, int prev_guess) {
    interpret(red, white, prev_guess);
    int guesssix = 0;
    for (int i = 0; i < 4; i++) {
        guesssix += ((prev_guess/(int)pow(10, 3 - i)) - (prev_guess/(int)pow(10, 4 - i))*10 - 1) * pow(6, 3 - i); 
    }
    while (allowed[guesssix][0] == 0) {
        guesssix = ( guesssix + 1) % 1296;
    }
    return 1000*allowed[guesssix][0] + 100*allowed[guesssix][1] + 10*allowed[guesssix][2] + allowed[guesssix][3];
}

int main(void) {
    create_list();
    for (int i = 0; i < 1296; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d", allowed[i][j]);
        }
        printf(" ");
    }
    printf("%d", guess(1, 1, 1234));
    return 0;
}
