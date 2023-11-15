
#include <stdio.h>

int gcd(int a, int b) {
    int temp;
    while (b != 0) {
        temp = a - (a / b * b);
        a = b;
        b = temp;
    }
    return a;
}

int main(void) {
    int a, b;
    printf("Choose value for a: ");
    scanf("%d", &a);
    printf("Choose value for b: ");
    scanf("%i", &b);
    printf("The greatest common divisor of %d and %d is %d.\n", a, b, gcd(a, b));
    return 0;
}
