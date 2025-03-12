#ifndef TWOCYCLIST_H
#define TWOCYCLIST_H

struct twocyclist {
    int value;
    struct twocyclist* prev;
    struct twocyclist* next;
};

struct twocyclist* insert(struct twocyclist* list, int value);
int merge(struct twocyclist* list1, struct twocyclist* list2);

#endif