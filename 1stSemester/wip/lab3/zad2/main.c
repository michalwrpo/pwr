// Zadanie 2, main.c Michał Waluś

#include <stdio.h>
#include <math.h>
#include "funs.h"

int main(void) {
    for (int k = 1; k <= 8; k++)
    {
        printf("Miejsce zerowe: %lf\n", rozwiazanie(2, 4, pow(10, -k)));
    }
    return 0;
}
