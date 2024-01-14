//Zadanie 2, main.c Michał Waluś

#include <stdio.h>
#include "funs.h"

int main(void) {
    int white = 0, red = 0;
    int prev_guess = 0, new_guess, try = 1;
    while (red != 4) {
        new_guess = guess(white, red, prev_guess, try);
        printf("%d. Guess: %d\n", try, new_guess);
        printf("Red: ");
        scanf("%d", &red);
        printf("White: ");
        scanf("%d", &white);
        prev_guess = new_guess;
        try++;
    }
    
    return 0;
}
