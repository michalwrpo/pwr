// Zadanie 3, zadanie3.c Michał Waluś

#include <math.h>
#include <stdio.h>

int main(void) {
    double e = exp(1.0), ans, root = 2.0 * 3.1415 * 1000;
    for(int i; i < 10; i++) {
        root = sqrt(root);
    }
    ans = root * 1000 / e;
    printf("%lf\n", ans);
}
