// Zadanie 2, rozwiazanie.c Michał Waluś

#include "funs.h"

double rozwiazanie(double a, double b, double eps) {
    while(b-a > eps) {
        double c = (a + b) / 2;
        if(f(c) == 0) {
            return c;
        } else if (f(c)*f(a) < 0) {
            b = c;
        } else{
            a = c;
        }
    }
    return (a+b)/2;
}
