// Zadanie 5, zadanie5.c Michał Waluś

#include <stdio.h>

int sigma(int n) {
    int ans = 0;
    for(int i = 1; i < n; i++) {
        if(n % i == 0) {
            ans += i;
        }
    }
    return ans;
}

int main(void) {
    printf("%d\n", sigma(6));
    for(int i = 1; i <= 1000; i++) {
        int j = sigma(i);
        if (i == j) {
            printf("Liczba doskonała: %d\n", i);
        }
        if (i <= j) {
            if (i == sigma(j)) {
                printf("Para zaprzyjaźniona: (%d, %d)\n", i, j);
            }
        }
    }
}
