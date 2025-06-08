#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <time.h>

#include "graph.h"

int compare1(const void *a, const void *b) {
    double arg1 = ((const edge*)a)->weight;
    double arg2 = ((const edge*)b)->weight;
    return (arg1 > arg2) - (arg1 < arg2);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s [n]\n", argv[0]);
        return -1;
    }

    if (atoi(argv[1]) < 1) {
        printf("n (number of vertices) must be a postive number\n");
        return -1;
    }

    // default stack wasn't enough matrices big enough
    const rlim_t kStackSize = (unsigned long)(8 * 1024 * 1024) * 1024;   // min stack size = 8 GB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0) 
                fprintf(stderr, "setrlimit returned result = %d\n", result);
        }
    }
    
    unsigned int len = atoi(argv[1]);
    unsigned int size = len * (len - 1) >> 1;

    edge* edges[size];

    makeGraphList(len, edges);

    // for (unsigned int i = 0; i < size; i++) {
    //     edge* e = edges[i];
    //     printf("(%d, %d, %.2f) ", e->vertex1, e->vertex2, e->weight);
    // }
    // printf("\n");

    edge* mst[len - 1];

    clock_t start = clock();
    kruskal(len, edges, mst);
    clock_t end = clock();

    printf("Kruskal %d %.6f\n", len, ((double) (end - start)) / CLOCKS_PER_SEC);

    // for (unsigned int i = 0; i < len - 1; i++) {
    //     edge* e = mst[i];
    //     printf("(%d -> %d) ", e->vertex1, e->vertex2);
    // }
    // printf("\n");
    

    return 0;
}