// Zadanie 1, palindrom.c Michał Waluś

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "funs.h"

bool palindrom(char napis[]) {
    for (int i = 0; i < (int) (strlen(napis))/2; i++) {
        if(napis[i] != napis[strlen(napis) - 1 - i]) {
            return false;
        }
    }
    return true;
}
