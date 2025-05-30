#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "mtwister.h"
#include "bst.h"

#define RANDOM_OPERATIONS 30

int main() {
    MTRand r = seedRand(time(NULL));

    int inserts[RANDOM_OPERATIONS];
    int deletes[RANDOM_OPERATIONS];

    int left = RANDOM_OPERATIONS;
    int index;

    struct BST tree;
    tree.root = NULL;

    // inserts in order
    // clear the arrays
    for (int i = 0; i < RANDOM_OPERATIONS; i++) {
        inserts[i] = i + 1;
        deletes[i] = 0;
    }

    // deletes
    while (left > 0) {
        index = genRandLong(&r) %  RANDOM_OPERATIONS;
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
        BST_insert(&tree, inserts[i]);
        BST_print(&tree);
    }
    
    for (int i = 0; i < RANDOM_OPERATIONS; i++) {
        printf("\ndelete %d\n", deletes[i]);
        BST_delete(&tree, deletes[i]);
        BST_print(&tree);
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
        index = genRandLong(&r) %  RANDOM_OPERATIONS;
        if (inserts[index] > 0) {
            continue;
        }
        
        inserts[index] = left;
        left--;
    }

    left = RANDOM_OPERATIONS;

    // deletes
    while (left > 0) {
        index = genRandLong(&r) %  RANDOM_OPERATIONS;
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
        BST_insert(&tree, inserts[i]);
        BST_print(&tree);
    }
    
    for (int i = 0; i < RANDOM_OPERATIONS; i++) {
        printf("\ndelete %d\n", deletes[i]);
        BST_delete(&tree, deletes[i]);
        BST_print(&tree);
    }

    return 0;
}