
#include <stdio.h>


int x = 0, y = 1;
int exEuclidean(int a, int b) {
    int q, r, temp;
    q = a / b;
    r = a - q * b;
    if (r != 0) {
        exEuclidean(b, r);
        temp = y;
        y = x - y * q;
        x = temp;
    }
    return a * x + b * y;
}

int main(void) {
    int a, b, c, gcd, q, a1, b1;
    printf("Choose value for a: ");
    scanf("%d", &a);
    printf("Choose value for b: ");
    scanf("%d", &b);
    printf("Choose value for c: ");
    scanf("%d", &c);
    gcd = exEuclidean(a, b);
    if (c % gcd != 0) {
        printf("No integer solutions.\n");
    } else {
        x *= c / gcd;
        y *= c / gcd;
        a1 = a / gcd;
        b1 = b / gcd;
        printf("%d * (%d) + %d * (%d) = %d\n", a, x, b, y, c);
        q = x / b1;
        x -= q * b1;
        y += q * a1;
        if (x < - b1 / 2 || x > b1 / 2) {
            x += b1;
            y -= a1;
        }
        printf("%d * (%d) + %d * (%d) = %d\n", a, x, b, y, c);
    }
    return 0;
}
