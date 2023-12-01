// Zadanie 1, main.c

#include <stdio.h>
#include <stdbool.h>
#include "funs.h"

int main(void) {
    char napis[] = "abcddcba";
    int czyPalindrom = palindrom(napis);
    switch (czyPalindrom)
    {
    case 0:
        printf("Napis \"%s\" nie jest palindromem.\n", napis);
        break;
    
    case 1:
        printf("Napis \"%s\" jest palindromem.\n", napis);
        break;
    }
    return 0;
}