//Zadanie 2, decode.c Michał Waluś

#include <math.h>
#include <stdio.h>
#include "funs.h"


int allowed[4][6] = {{1, 2 , 3, 4, 5, 6}, {1, 2 , 3, 4, 5, 6}, {1, 2 , 3, 4, 5, 6}, {1, 2 , 3, 4, 5, 6}};
int try = 0;

int count(int guess) {
    int amount = 0;
    int array[4];
    for (int i = 0; i < 4; i++) {
        array[i] = (guess/(int)pow(10, 3 - i)) - (guess/(int)pow(10, 4 - i))*10;
    }
    for (int i = 0; i < 4; i++) {
        amount += pow(10, array[i]-1);
    }
    printf("(%d, %d) ", guess, amount);
    return amount;
}

void interpret(int white, int red, int guess) {
    int array[4];
    for (int i = 0; i < 4; i++) {
        array[i] = (guess/(int)pow(10, 3 - i)) - (guess/(int)pow(10, 4 - i))*10;
    }
    if(white == 0 && red == 0) {
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++) {
                allowed[i][array[j] - 1] = 0;
            }
        }
    } else if (red == 0) {
        for (int i = 0; i < 4; i++) {
            allowed[i][array[i] - 1] = 0;
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            printf("%d ", allowed[i][j]);
        }
        printf("| ");
    }
    printf("\n");
}

int shuffle(int guess, int try) {
    int array[4];
    for (int i = 0; i < 4; i++) {
        array[i] = (guess/(int)pow(10, 3 - i)) - (guess/(int)pow(10, 4 - i))*10;
    }
    for (int i = 0; i < 4; i++) {
        if(try < 4) {
            array[i] = (array[i] + 1) % 6 + 1;
        } else {
            array[i] = (array[i] + i + try) % 6 + 1;
        }
        while (allowed[i][array[i] - 1] == 0) {
            array[i] = array[i] % 6 + 1;
        }
    }
    return 1000*array[0] + 100*array[1] + 10*array[2] + array[3];
}

int permutate(int prev_guess, int try) {
    int array[4];
    for (int i = 0; i < 4; i++) {
        array[i] = (prev_guess/(int)pow(10, 3 - i)) - (prev_guess/(int)pow(10, 4 - i))*10;
    }
    int temp;
    int guess = prev_guess;
    while (guess == prev_guess) {
        temp = array[try % 4];
        array[try % 4] = array[(try * (try + 1)) % 4];
        array[(try * (try + 1)) % 4] = temp;
        guess = 1000*array[0] + 100*array[1] + 10*array[2] + array[3];
        try++;
    }
    return guess;
}

int guess(int white, int red, int prev_guess, int try) {
    if (try == 1) {
        return 1122;
    }
    interpret(white, red, prev_guess);
    if(white + red == 4) {
        return permutate(prev_guess, try);
    }
    int new_guess = shuffle(prev_guess, try);
    printf("%d\n", new_guess);
    return new_guess;
}
