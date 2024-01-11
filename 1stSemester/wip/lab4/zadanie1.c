//Zadanie 1, zadanie1.c Michał Waluś

#include <stdio.h>
#include <stdbool.h>

bool match(char* wzorzec, char* lancuch) {
    if(*wzorzec == '\0') {
        if(*lancuch == '\0') {
            return true;
        }
        return false;
    }
    if(*wzorzec == *lancuch || *wzorzec == '?') {
        return match((wzorzec + 1), (lancuch + 1));
    } else if (*wzorzec == '*') {
        if(match((wzorzec + 1), lancuch)) {
            return true;
        } else if(match((wzorzec), (lancuch + 1))) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}  

int main(void) {
    printf("%d\n", match("a*b*a", "abababababababababababa"));
    printf("%d\n", match("a*b*a", "ababababababababababab"));
    
}
