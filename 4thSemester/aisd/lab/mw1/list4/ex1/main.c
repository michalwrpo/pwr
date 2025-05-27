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

    struct BST_Node *root = NULL;
    printf("\ninsert %d\n", inserts[0]);
    root = BST_insert(root, inserts[0]);
    BST_print(root);
    for (int i = 1; i < RANDOM_OPERATIONS; i++) {
        printf("\ninsert %d\n", inserts[i]);
        BST_insert(root, inserts[i]);
        BST_print(root);
    }
    
    for (int i = 0; i < RANDOM_OPERATIONS; i++) {
        printf("\ndelete %d\n", deletes[i]);

        // whole tree has been deleted
        if (BST_delete(root, deletes[i]) == 1)
            root = NULL;
        BST_print(root);
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

    root = NULL;
    printf("\ninsert %d\n", inserts[0]);
    root = BST_insert(root, inserts[0]);
    BST_print(root);
    for (int i = 1; i < RANDOM_OPERATIONS; i++) {
        printf("\ninsert %d\n", inserts[i]);
        BST_insert(root, inserts[i]);
        BST_print(root);
    }
    
    for (int i = 0; i < RANDOM_OPERATIONS; i++) {
        printf("\ndelete %d\n", deletes[i]);

        // whole tree has been deleted
        if (BST_delete(root, deletes[i]) == 1)
            root = NULL;
        BST_print(root);
    }

    return 0;
}