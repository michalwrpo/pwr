// Zadanie 3, zadanie3.c Michał Waluś

#include <math.h>
#include <stdio.h>

int main(void) {
    double product = 1;
    for (int i = 1; i <= 500; i++) {
        product *= pow( (i * (1001-i)), 1.0/100);
    }
    printf("%lf\n", pow(product, 1.0/10));
    return 0;
}
