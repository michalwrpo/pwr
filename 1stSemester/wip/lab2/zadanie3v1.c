// Zadanie 3, zadanie3.c Michał Waluś

#include <math.h>
#include <stdio.h>

int main(void) {
    double e = exp(1.0), ans, root = 2.0 * 3.1415 * 1000;
    root = pow(root, 1.0/1000);
    ans = root * 1000 / e;
    printf("%lf\n", ans);
    return 0;
}
