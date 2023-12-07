// Zadanie 3, phi.c Michał Waluś

#include "funs.h"

int phi(long int n) {
    long int ans = n, k = 3;
    if(n % 2 == 0) {
        ans /= 2;
        while (n % 2 == 0) {
            n /= 2;
        }
    }
    while(k * k <= n) {
        if(n % k == 0) {
            ans -= ans / k;
            while (n % k == 0) {
                n /= k;
            }
        }
        k += 2;
    }
    if(n != 1) {
        ans -= ans / n;
    }
    return ans;     
}
