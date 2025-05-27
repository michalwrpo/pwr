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

    struct RBT_Node *root = NULL;
    printf("\ninsert %d\n", inserts[0]);
    root = RBT_insert(root, inserts[0], &comps, &r, &w, true);
    RBT_print(root);
    for (int i = 1; i < RANDOM_OPERATIONS; i++) {
        printf("\ninsert %d\n", inserts[i]);
        root = RBT_insert(root, inserts[i], &comps, &r, &w, true);
        RBT_print(root);
    }
    
    for (int i = 0; i < RANDOM_OPERATIONS; i++) {
        printf("\ndelete %d\n", deletes[i]);

        // whole tree has been deleted
        if (RBT_delete(root, deletes[i], &comps, &r, &w, true) == 1)
            root = NULL;
        RBT_print(root);
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

    root = NULL;
    for (int i = 0; i < RANDOM_OPERATIONS; i++) {
        printf("\ninsert %d\n", inserts[i]);
        RBT_insert(root, inserts[i], &comps, &r, &w, true);
        RBT_print(root);
    }
    
    for (int i = 0; i < RANDOM_OPERATIONS; i++) {
        printf("\ndelete %d\n", deletes[i]);

        // whole tree has been deleted
        if (RBT_delete(root, deletes[i], &comps, &r, &w, true) == 1)
            root = NULL;
        RBT_print(root);
    }

    return 0;
}