#include "string_helper.h"

char* strcpy(char* dest, const char* src) {
    int i{ 0 };
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    
    dest[i] = '\0';

    return dest;
}

int strlen(char* str) {
    int i{ 0 };
    while (str[i] != '\0') i++;
    return i;
}

