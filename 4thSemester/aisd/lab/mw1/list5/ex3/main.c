#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "mtwister.h"
#include "binHeap.h"

#define MAX_KEY 100000

int main(void) {
    MTRand r = seedRand(time(NULL));
    long comps = 0;

    BinaryHeap* H1 = makeHeap();    
    BinaryHeap* H2 = makeHeap();

    for (int i = 0; i < 500; i++) {
        heapInsert(H1, genRandLong(&r) % MAX_KEY, &comps);
        printf("H1 insert %d %ld\n", i, comps);
        comps = 0;
        heapInsert(H2, genRandLong(&r) % MAX_KEY, &comps);
        printf("H2 insert %d %ld\n", i, comps);
        comps = 0;
    }

    heapUnion(H1, H2, &comps);
    printf("H Union %ld\n", comps);
    comps = 0;

    BHNode* x;
    for (int i = 0; i < 1000; i++) {
        x = heapExtractMin(H1, &comps);
        printf("H Extract %d %ld\n", i, comps);
        comps = 0;
        // printf("%d\n", x->key);
        free(x);
    }

    if (H1->head == NULL) {
        printf("empty\n");
    } else {
        printf("not empty\n");
    }
    
    free(H1);    

    return 0;
}