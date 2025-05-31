#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "mtwister.h"
#include "rbt.h"

#define RANDOM_OPERATIONS 30

int main() {
    MTRand rand = seedRand(time(NULL));

    long comps = 0, r = 0, w = 0;

    int inserts[RANDOM_OPERATIONS];
    int deletes[RANDOM_OPERATIONS];

    int left = RANDOM_OPERATIONS;
    unsigned int index;

    struct RBT tree;
    struct RBT_Node nil;
    nil.red = false;
    nil.height = 0;
    nil.left = &nil;
    nil.right = &nil;
    nil.parent = &nil;

    tree.nil = &nil;
    tree.root = &nil;

    // inserts in order
    // clear the arrays
    for (int i = 0; i < RANDOM_OPERATIONS; i++) {
        inserts[i] = i + 1;
        deletes[i] = 0;
    }

    // deletes
    while (left > 0) {
        index = genRandLong(&rand) %  RANDOM_OPERATIONS;
        if (deletes[index] > 0) {
            continue;
        }
        
        deletes[index] = left;
        left--;
    }

    printf(" --- INCREASING INSERTS --- \n");
    printf("Inserts: ");
    for (int i = 0; i < RANDOM_OPERATIONS; i++) {
        printf("%d ", inserts[i]);
    }
    printf("\n");

    printf("Deletes: ");
    for (int i = 0; i < RANDOM_OPERATIONS; i++) {
        printf("%d ", deletes[i]);
    }
    printf("\n");

    for (int i = 0; i < RANDOM_OPERATIONS; i++) {
        printf("\ninsert %d\n", inserts[i]);
        RBT_insert(&tree, inserts[i], &comps, &r, &w, true);
        RBT_print(&tree);
    }
    
    for (int i = 0; i < RANDOM_OPERATIONS; i++) {
        printf("\ndelete %d\n", deletes[i]);
        RBT_delete(&tree, deletes[i], &comps, &r, &w, true);
        RBT_print(&tree);
    }

    // random inserts
    // clear the arrays
    for (int i = 0; i < RANDOM_OPERATIONS; i++) {
        inserts[i] = 0;
        deletes[i] = 0;
    }

    left = RANDOM_OPERATIONS;

    // inserts
    while (left > 0) {
        index = genRandLong(&rand) %  RANDOM_OPERATIONS;
        if (inserts[index] > 0) {
            continue;
        }
        
        inserts[index] = left;
        left--;
    }

    left = RANDOM_OPERATIONS;

    // deletes
    while (left > 0) {
        index = genRandLong(&rand) %  RANDOM_OPERATIONS;
        if (deletes[index] > 0) {
            continue;
        }
        
        deletes[index] = left;
        left--;
    }

    printf("\n --- RANDOM INSERTS --- \n");
    printf("Inserts: ");
    for (int i = 0; i < RANDOM_OPERATIONS; i++) {
        printf("%d ", inserts[i]);
    }
    printf("\n");

    printf("Deletes: ");
    for (int i = 0; i < RANDOM_OPERATIONS; i++) {
        printf("%d ", deletes[i]);
    }
    printf("\n");

    for (int i = 0; i < RANDOM_OPERATIONS; i++) {
        printf("\ninsert %d\n", inserts[i]);
        RBT_insert(&tree, inserts[i], &comps, &r, &w, true);
        RBT_print(&tree);
    }
    
    for (int i = 0; i < RANDOM_OPERATIONS; i++) {
        printf("\ndelete %d\n", deletes[i]);
        RBT_delete(&tree, deletes[i], &comps, &r, &w, true);
        RBT_print(&tree);
    }

    return 0;
}