// Zadanie 2, zadanie2.c Michał Waluś

#include <stdio.h>

int main(void) {
    double n = 0, sum = 0;
    while (sum <= 10) {
        n ++;
        sum += 1/n;
    }
    printf("n: %lf\nsum: %lf\n", n, sum);
    return 0;
}
