// Zadanie 4, Michał Waluś

#include <stdio.h>

int main(void) {
    int n;
    printf("Podaj liczbę n: ");
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n-1-i; j++) {
            printf(" ");
        }
        for(int j = 0; j < 2 * i + 1; j++) {
            printf("*");
        }
        for(int j = 0; j < n-1-i; j++) {
            printf(" ");
        }
        printf("\n");
    }
    return 0;
}
