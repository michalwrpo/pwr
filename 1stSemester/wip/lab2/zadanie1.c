// Zadanie 1, zadanie1.c Michał Waluś

#include <stdio.h>

int main(void) {
    int R;
    printf("Podaj rok: ");
    scanf("%d", &R);
    if (R % 400 == 0) {
        printf("Rok %d jest przestępny.\n", R);
    } else if (R % 100 == 0) {
        printf("Rok %d jest zwykły.\n", R);
    } else if (R % 4 ==0) {
        printf("Rok %d jest przestępny.\n", R);
    } else {
        printf("Rok %d jest zwykły.\n", R);
    }
    return 0;
}
