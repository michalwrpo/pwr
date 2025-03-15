#include <stdlib.h>

#include "twocyclist.h"

struct twocyclist* insert(struct twocyclist* list, int value) {
    struct twocyclist* node = (struct twocyclist*)malloc(sizeof(struct twocyclist));

    if (!node) {
        return NULL; // malloc failure
    }

    node->value = value;

    if (!list) {
        node->prev = node;
        node->next = node;
        return node;
    }

    node->prev = list;
    node->next = list->next;
    list->next->prev = node;
    list->next = node;

    return list;
}

int merge(struct twocyclist* list1, struct twocyclist* list2) {
    if (!list1 || !list2)
            return -1;
    
    struct twocyclist* temp = list2->next;
    list1->next->prev = list2;
    list2->next->prev = list1;

    list2->next = list1->next;
    list1->next = temp;

    return 0;
}

void delete(struct twocyclist* list) {
    if (!list) {
        return;
    }

    if (list == list->next) {
        free(list);
        return;
    }
    
    struct twocyclist* cur = list;
    struct twocyclist* next = list->next;

    while (next != list) {
        free(cur);
        cur = next;
        next = cur->next;
    }
}