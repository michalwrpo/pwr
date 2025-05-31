#include <stdio.h>
#include <time.h>
#include <sys/resource.h>
#include <stdbool.h>

#include "mtwister.h"
#include "rbt.h"

#define START 10000
#define INCREASE 10000
#define MAX 100000
#define REPEATS 20

void stats(long* tot_c, long* tot_r, long* tot_w, long* tot_h, long* max_c, long* max_r, long* max_w, long *c, long *r, long *w, long h) {
    (*tot_c) += *c;
    (*tot_r) += *r;
    (*tot_w) += *w;
    (*tot_h) += h;
    
    *max_c = (*c > (*max_c) ? *c : *max_c);
    *max_r = (*r > (*max_r) ? *r : *max_r);
    *max_w = (*w > (*max_w) ? *w : *max_w);

    *c = 0;
    *r = 0;
    *w = 0;
}

int main() {
    // default stack wasn't enough for 100 000 inserts in ascending order
    const rlim_t kStackSize = 1024 * 1024 * 1024;   // min stack size = 1 GB
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
            {
                fprintf(stderr, "setrlimit returned result = %d\n", result);
            }
        }
    }

    // printf("operation n avg_comps max_comps avg_reads max_reads avg_writes max_writes avg_H max_H\n");
    MTRand gen_r = seedRand(time(NULL));

    unsigned int left, index;
    long comps, r, w, max_c, max_r, max_w, max_h;
    long total_c, total_r, total_w, total_h;
    
    struct RBT_Node nil;
    nil.left = &nil;
    nil.right = &nil;
    nil.parent = &nil;
    nil.red = false;
    nil.height = 0;

    struct RBT tree;
    tree.nil = &nil;
    tree.root = &nil;

    // random inserts
    for (unsigned int n = START; n <= MAX; n += INCREASE) {
        unsigned int inserts[n];
        unsigned int deletes[n];

        for (unsigned int k = 0; k < REPEATS; k++) {
            comps = 0;
            r = 0;
            w = 0;
            max_c = 0;
            max_r = 0;
            max_w = 0;
            max_h = 0;
            total_c = 0;
            total_r = 0;
            total_w = 0;
            total_h = 0;
            
            // clear the arrays
            for (unsigned int i = 0; i < n; i++) {
                inserts[i] = 0;
                deletes[i] = 0;
            }

            left = n;

            // inserts
            while (left > 0) {
                index = genRandLong(&gen_r) % n;
                if (inserts[index] > 0) {
                    continue;
                }
                
                inserts[index] = left;
                left--;
            }

            left = n;

            // deletes
            while (left > 0) {
                index = genRandLong(&gen_r) % n;
                if (deletes[index] > 0) {
                    continue;
                }
                
                deletes[index] = left;
                left--;
            }
            
            for (unsigned  int i = 0; i < n; i++) {
                RBT_insert(&tree, inserts[i], &comps, &r, &w, true);
                stats(&total_c, &total_r, &total_w, &total_h, &max_c, &max_r, &max_w, &comps, &r, &w, RBT_height(tree.root));
            }
            
            max_h = RBT_height(tree.root);
            printf("rand insert %d %ld %ld %ld %ld %ld %ld %ld %ld\n", n, total_c/n, max_c, total_r/n, max_r, total_w/n, max_w, total_h/n, max_h);

            max_c = 0;
            max_r = 0;
            max_w = 0;
            total_c = 0;
            total_r = 0;
            total_w = 0;
            total_h = 0;

            for (unsigned int i = 0; i < n; i++) {        
                RBT_delete(&tree, deletes[i], &comps, &r, &w, true);
                stats(&total_c, &total_r, &total_w, &total_h, &max_c, &max_r, &max_w, &comps, &r, &w, RBT_height(tree.root));
            }

            printf("rand delete %d %ld %ld %ld %ld %ld %ld %ld %ld\n", n, total_c/n, max_c, total_r/n, max_r, total_w/n, max_w, total_h/n, max_h);
        }
    }

    // inserts in order
    for (unsigned int n = START; n <= MAX; n += INCREASE) {
        unsigned int inserts[n];
        unsigned int deletes[n];
        
        // init inserts
        for (unsigned int i = 0; i < n; i++) {
            inserts[i] = i + 1;
        }

        for (unsigned int k = 0; k < REPEATS; k++) {
            comps = 0;
            r = 0;
            w = 0;
            max_c = 0;
            max_r = 0;
            max_w = 0;
            max_h = 0;
            total_c = 0;
            total_r = 0;
            total_w = 0;
            total_h = 0;

            // clear the array
            for (unsigned int i = 0; i < n; i++) {
                deletes[i] = 0;
            }

            left = n;

            // deletes
            while (left > 0) {
                index = genRandLong(&gen_r) % n;
                if (deletes[index] > 0) {
                    continue;
                }
                
                deletes[index] = left;
                left--;
            }
            
            for (unsigned  int i = 0; i < n; i++) {
                RBT_insert(&tree, inserts[i], &comps, &r, &w, true);
                stats(&total_c, &total_r, &total_w, &total_h, &max_c, &max_r, &max_w, &comps, &r, &w, RBT_height(tree.root));
            }
            
            max_h = RBT_height(tree.root);
            printf("asc insert %d %ld %ld %ld %ld %ld %ld %ld %ld\n", n, total_c/n, max_c, total_r/n, max_r, total_w/n, max_w, total_h/n, max_h);

            max_c = 0;
            max_r = 0;
            max_w = 0;
            total_c = 0;
            total_r = 0;
            total_w = 0;
            total_h = 0;

            for (unsigned int i = 0; i < n; i++) {        
                RBT_delete(&tree, deletes[i], &comps, &r, &w, true);
                stats(&total_c, &total_r, &total_w, &total_h, &max_c, &max_r, &max_w, &comps, &r, &w, RBT_height(tree.root));
            }

            printf("asc delete %d %ld %ld %ld %ld %ld %ld %ld %ld\n", n, total_c/n, max_c, total_r/n, max_r, total_w/n, max_w, total_h/n, max_h);
        }
    }

    return 0;
}