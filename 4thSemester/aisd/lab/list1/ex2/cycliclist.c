#include <stdlib.h>

#include "cycliclist.h"

struct cycliclist* insert(struct cycliclist* list, int value) {
    struct cycliclist* node = (struct cycliclist*)malloc(sizeof(struct cycliclist));

    if (!node) {
        return NULL; // malloc failure
    }

    node->value = value;

    if (!list) {
        node->next = node;
        return node;
    }

    node->next = list->next;
    list->next = node;

    return list;
}

int merge(struct cycliclist* list1, struct cycliclist* list2) {
    if (list1 == 0 || list2 == 0)
        return -1;
    
    struct cycliclist* temp = list2->next;
    list2->next = list1->next;
    list1->next = temp;

    return 0;
}