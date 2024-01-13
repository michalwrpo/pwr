//Zadanie 2, decode.c Michał Waluś

#include <math.h>
#include "funs.h"



void interpret(int white, int red, int guess) {
    int allowed[4][6] = {{1, 2 , 3, 4, 5, 6}, {1, 2 , 3, 4, 5, 6}, {1, 2 , 3, 4, 5, 6}, {1, 2 , 3, 4, 5, 6}};
    int array[4];
    for (int i = 0; i < 4; i++) {
        array[i] = ((guess/pow(10, 3 - i))*pow(10, 3 - i)) - ((guess/pow(10, 4 - i))*pow(10, 4 - i));
        print("%d", array[i]);
    }
    if(white == 0 && red == 0) {
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++) {
                allowed[i][array[j] - 1] = 0;
            }
        }
    } else if (white == 0) {
        for (int i = 0; i < 4; i++) {
            allowed[i][array[i] - 1] = 0;
        }
        
    }
    
}
