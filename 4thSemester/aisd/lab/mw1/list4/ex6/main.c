#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#include "mtwister.h"
#include "splaytree.h"

void stats(long* tot_c, long* tot_r, long* tot_w, long* tot_h, long* max_c, long* max_r, long* max_w, long* max_h, long *c, long *r, long *w, long h) {
    (*tot_c) += *c;
    (*tot_r) += *r;
    (*tot_w) += *w;
    (*tot_h) += h;
    
    *max_c = (*c > (*max_c) ? *c : *max_c);
    *max_r = (*r > (*max_r) ? *r : *max_r);
    *max_w = (*w > (*max_w) ? *w : *max_w);
    *max_h = (h > (*max_h) ? h : *max_h);

    *c = 0;
    *r = 0;
    *w = 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s [n]\n", argv[0]);
        return -1;
    }

    if (atoi(argv[1]) < 1) {
        printf("n must be a postive number\n");
        return -1;
    }
    
    unsigned int n = atoi(argv[1]);
    
    MTRand gen_r = seedRand(time(NULL));

    unsigned int left, index;
    long comps, r, w, max_c, max_r, max_w, max_h;
    long total_c, total_r, total_w, total_h;
    struct Splay_Tree tree;

    tree.root = NULL;
    
    unsigned int inserts[n];
    unsigned int deletes[n];
    
    // inserts in order
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
    
    for (unsigned int i = 0; i < n; i++) {
        Splay_insert(&tree, i + 1, &comps, &r, &w, true);
        stats(&total_c, &total_r, &total_w, &total_h, &max_c, &max_r, &max_w, &max_h, &comps, &r, &w, Splay_height(tree.root));
    }

    
    printf("asc insert %d %ld %ld %ld %ld %ld %ld %ld %ld\n", n, total_c, max_c, total_r, max_r, total_w, max_w, total_h, max_h);

    max_c = 0;
    max_r = 0;
    max_w = 0;
    max_h = 0;
    total_c = 0;
    total_r = 0;
    total_w = 0;
    total_h = 0;

    for (unsigned int i = 0; i < n; i++) {                        
        Splay_delete(&tree, deletes[i], &comps, &r, &w, true);
        stats(&total_c, &total_r, &total_w, &total_h, &max_c, &max_r, &max_w, &max_h, &comps, &r, &w, Splay_height(tree.root));
    }

    printf("asc delete %d %ld %ld %ld %ld %ld %ld %ld %ld\n", n, total_c, max_c, total_r, max_r, total_w, max_w, total_h, max_h);

    // random inserts
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
    
    for (unsigned int i = 0; i < n; i++) {
        Splay_insert(&tree, inserts[i], &comps, &r, &w, true);
        stats(&total_c, &total_r, &total_w, &total_h, &max_c, &max_r, &max_w, &max_h, &comps, &r, &w, Splay_height(tree.root));    
    }
    
    printf("rand insert %d %ld %ld %ld %ld %ld %ld %ld %ld\n", n, total_c, max_c, total_r, max_r, total_w, max_w, total_h, max_h);

    max_c = 0;
    max_r = 0;
    max_w = 0;
    max_h = 0;
    total_c = 0;
    total_r = 0;
    total_w = 0;
    total_h = 0;

    for (unsigned int i = 0; i < n; i++) {                        
        Splay_delete(&tree, deletes[i], &comps, &r, &w, true);
        stats(&total_c, &total_r, &total_w, &total_h, &max_c, &max_r, &max_w, &max_h, &comps, &r, &w, Splay_height(tree.root));
    }

    printf("rand delete %d %ld %ld %ld %ld %ld %ld %ld %ld\n", n, total_c, max_c, total_r, max_r, total_w, max_w, total_h, max_h);

    return 0;
}