#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <time.h>

#include "graph.h"
#include "order.h"

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

    double edges[len][len];

    makeGraph(len, edges);

    int mst[len];

    prim(len, edges, mst);

    int ans = 0;
    order(mst, len, &ans);

    printf("%d %d\n", len, ans);

    return 0;
}