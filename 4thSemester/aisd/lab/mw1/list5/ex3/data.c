#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "mtwister.h"
#include "binHeap.h"

#define MAX_KEY 100000

int main(int argc, char** argv) {
        if (argc != 2) {
        printf("Usage: %s [n]\n", argv[0]);
        return -1;
    }

    if (atoi(argv[1]) < 1) {
        printf("n must be a postive number\n");
        return -1;
    }

    int n = atoi(argv[1]);

    struct timeval now;
    gettimeofday(&now, NULL);
    MTRand r = seedRand(now.tv_usec);
    long comps = 0;

    BinomialHeap* H1 = makeHeap();    
    BinomialHeap* H2 = makeHeap();

    for (int i = 0; i < n; i++) {
        heapInsert(H1, genRandLong(&r) % MAX_KEY, &comps);
        heapInsert(H2, genRandLong(&r) % MAX_KEY, &comps);
    }

    heapUnion(H1, H2, &comps);

    BHNode* x;
    for (int i = 0; i < 2 * n; i++) {
        x = heapExtractMin(H1, &comps);
        free(x);
    }

    printf("%d %ld\n", n, comps);
    
    free(H1);    

    return 0;
}