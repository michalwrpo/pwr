#include <stdio.h>

#include "twocyclist.h"
#include "mtwister.h"

#define RND_NUMS 10000
#define RND_MAX 100000
#define SEARCHES 1000

int main() {
    struct twocyclist* list1 = insert(0, 19);
    struct twocyclist* list2 = insert(0, 29);

    for (int i = 0; i < 9; i++) {
        insert(list1, 10 + i);
        insert(list2, 20 + i);
    }
    
    struct twocyclist* loopptr = list1;

    printf("List 1:\n");
    do {
        printf("%d->", loopptr->value);
        loopptr = loopptr->next;
    } while (loopptr != list1);

    loopptr = list2;

    printf("\nList 2:\n");
    do {
        printf("%d->", loopptr->value);
        loopptr = loopptr->next;
    } while (loopptr != list2);

    merge(list1, list2);

    loopptr = list1;

    printf("\nMerged list:\n");

    do {
        printf("%d->", loopptr->value);
        loopptr = loopptr->next;
    } while (loopptr != list1);

    loopptr = list1;

    printf("\nMerged list (other direction):\n");

    do {
        printf("%d->", loopptr->value);
        loopptr = loopptr->prev;
    } while (loopptr != list1);

    printf("\n");

    printf("Cost of a search:\n");

    MTRand r = seedRand(1);

    int T[RND_NUMS];

    for (int i = 0; i < RND_NUMS; i++) {
        T[i] = genRandLong(&r) % (RND_MAX + 1);
    }
    
    struct twocyclist* list3;
    
    for (int i = 0; i < RND_NUMS; i++) {
        list3 = insert(list3, T[i]);
    }

    long cost = 0;

    for (int i = 0; i < SEARCHES; i++) {
        loopptr = list3;
        int num = T[genRandLong(&r) % RND_NUMS];
        if (genRandLong(&r) % 2) {
            while (loopptr->value != num) {
                loopptr = loopptr->next;
                cost++;
            }
        } else {
            while (loopptr->value != num) {
                loopptr = loopptr->prev;
                cost++;
            }
        }
        cost++;
    }

    double avgcost = (double)cost / SEARCHES;

    printf("Average cost (from list): %f\n", avgcost);

    cost = 0;

    for (int i = 0; i < SEARCHES; i++) {
        loopptr = list3;
        int num = genRandLong(&r) % RND_MAX;
        int i = 0;

        if (genRandLong(&r) % 2) {
            while (loopptr->value != num && i < RND_NUMS) {
                loopptr = loopptr->next;
                cost++;
                i++;
            }
        } else {
            while (loopptr->value != num && i < RND_NUMS) {
                loopptr = loopptr->prev;
                cost++;
                i++;
            }
        }
        
        cost++;
    }

    avgcost = (double)cost / SEARCHES;

    printf("Average cost (from interval): %f\n", avgcost);

    return 0;
}