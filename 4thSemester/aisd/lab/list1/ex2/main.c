#include <stdio.h>

#include "cycliclist.h"

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

    return 0;
}