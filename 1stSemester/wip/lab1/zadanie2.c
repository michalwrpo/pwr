// Zadanie 2, zadanie2.c Michał Waluś

#include <math.h>
#include <stdio.h>

int main(void) {
    double a, b, c, x1, x2, delta;
    printf("Wybierz wartość dla a: ");
    scanf("%lf", &a);
    printf("Wybierz wartość dla b: ");
    scanf("%lf", &b);
    printf("Wybierz wartość dla c: ");
    scanf("%lf", &c);
    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                printf("Wszystkie liczby rzeczywiste spełniają to równanie.\n");
            } else {
                printf("Brak rozwiązań.\n");
            }
        } else {
            x1 = -c/b;
            printf("1 rozwiązanie: %lf\n", x1);
        }
    } else {
        delta = b*b - 4*a*c;
        if (delta < 0) {
            printf("Brak rozwiązań.\n");
        } else if (delta == 0) {
            x1 = -b/(2 * a);
            printf("1 rozwiązanie: %lf\n", x1);
        } else {
            x1 = (-b + sqrt(delta))/(2 * a);
            x2 = (-b - sqrt(delta))/(2 * a);
            printf("2 rozwiązania: %lf, %lf\n", x1, x2);
        }
    }
    return 0;
}
