#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "mtwister.h"
#include "binHeap.h"

#define MAX_KEY 100000
#define REPETITIONS 5

int main(void) {
    struct timeval now;
    gettimeofday(&now, NULL);
    MTRand r = seedRand(now.tv_usec);

    long comps = 0;
    int result[1000];

    for (int k = 0; k < REPETITIONS; k++) {
        BinomialHeap* H1 = makeHeap();
        BinomialHeap* H2 = makeHeap();
    
        for (int i = 0; i < 500; i++) {
            heapInsert(H1, genRandLong(&r) % MAX_KEY, &comps);
            printf("%d H1 insert %d %ld\n", k, i, comps);
            comps = 0;
            heapInsert(H2, genRandLong(&r) % MAX_KEY, &comps);
            printf("%d H2 insert %d %ld\n", k, i, comps);
            comps = 0;
        }
    
        heapUnion(H1, H2, &comps);
        printf("%d H Union %ld\n", k, comps);
        comps = 0;
    
        BHNode* x;
        for (int i = 0; i < 1000; i++) {
            x = heapExtractMin(H1, &comps);
            printf("%d H Extract %d %ld\n", k, i, comps);
            comps = 0;
            result[i] = x->key;
            // printf("%d\n", x->key);
            free(x);
        }

        for (int i = 0; i < 999; i++) {
            if (result[i] > result[i+1]) {
                printf("not sorted\n");
                return -1;
            }    
        }
        
        if (H1->head != NULL) {
            printf("not empty\n");
            return -2;
        }
        
        free(H1);
    }    

    return 0;
}