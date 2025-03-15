#include <stdio.h>

#include "cycliclist.h"
#include "mtwister.h"

#define RND_NUMS 10000
#define RND_MAX 100000
#define SEARCHES 1000

int main() {
    struct cycliclist* list1 = insert(0, 19);
    struct cycliclist* list2 = insert(0, 29);

    for (int i = 0; i < 9; i++) {
        insert(list1, 10 + i);
        insert(list2, 20 + i);
    }
    
    struct cycliclist* loopptr = list1;

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

    printf("\n");

    delete(list1);

    printf("Cost of a search:\n");

    MTRand r = seedRand(1);

    int T[RND_NUMS];

    for (int i = 0; i < RND_NUMS; i++) {
        T[i] = genRandLong(&r) % (RND_MAX + 1);
    }
    
    struct cycliclist* list3;
    
    for (int i = 0; i < RND_NUMS; i++) {
        list3 = insert(list3, T[i]);
    }

    long cost = 0;

    for (int i = 0; i < SEARCHES; i++) {
        loopptr = list3;
        int num = T[genRandLong(&r) % RND_NUMS];

        while (loopptr->value != num) {
            loopptr = loopptr->next;
            cost++;
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

        while (loopptr->value != num && i < RND_NUMS) {
            loopptr = loopptr->next;
            cost++;
            i++;
        }
        cost++;
    }

    avgcost = (double)cost / SEARCHES;

    printf("Average cost (from interval): %f\n", avgcost);

    delete(list3);

    return 0;
}