//Zadanie 2, main.c Michał Waluś

#include <stdio.h>
#include <math.h>

int allowed[1296][4];
int left = 1296;

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
        int tallowed[4] = {allowed[i][0], allowed[i][1], allowed[i][2], allowed[i][3]};
        if (allowed[i][0] != 0) {
            int innerred = 0, innerwhite = 0;
            for (int j = 0; j < 4; j++) {
                if (allowed[i][j] == temporary[j]) {
                    innerred++;
                    temporary[j] = 0;
                    tallowed[j] = 7;
                }
            }
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 3; k++) {
                    if (tallowed[j] == temporary[(j + k + 1) % 4]) {
                        innerwhite++;
                        temporary[(j + k + 1) % 4] = 0;
                        break;
                    }
                }
            }
            if (innerred != red || innerwhite != white) {
                allowed[i][0] = 0;
                left--;
            }
        }
    }
}

int guess(int red, int white, int prev_guess) {
    interpret(red, white, prev_guess);
    int guesssix = 0;
    if (left == 0) {
        return 0;
    }
    
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
    int white = 0, red = 0, try = 1;
    int prev_guess = 1122, new_guess;
    printf("%d. Guess: 1122\n", try);
    printf("Red: ");
    scanf("%d", &red);
    printf("White: ");
    scanf("%d", &white);
    while (red != 4) {
        try++;
        new_guess = guess(red, white, prev_guess);
        if (new_guess == 0) {
            printf("You're cheating!\n");
            break;
        }
        printf("%d. Guess: %d\n", try, new_guess);
        printf("Red: ");
        scanf("%d", &red);
        printf("White: ");
        scanf("%d", &white);
        prev_guess = new_guess;
    }
    if (red == 4) {
        printf("I win!\n");
    }
    
    return 0;
}
