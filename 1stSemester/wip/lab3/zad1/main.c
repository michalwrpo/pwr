// Zadanie 1, main.c

#include <stdio.h>
#include <stdbool.h>
#include "funs.h"

int main(void) {
    char napis[] = "abcddcba";
    if(palindrom(napis) == 1)    {
        printf("Napis \"%s\" jest palindromem.\n", napis);
    } else {
        printf("Napis \"%s\" nie jest palindromem.\n", napis);
    }
    return 0;
}
