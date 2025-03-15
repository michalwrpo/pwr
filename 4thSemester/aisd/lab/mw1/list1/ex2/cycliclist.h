#ifndef CYCLICLIST_H
#define CYCLICLIST_H

struct cycliclist {
    int value;
    struct cycliclist* next;
};

struct cycliclist* insert(struct cycliclist* list, int value);
int merge(struct cycliclist* list1, struct cycliclist* list2);
void delete(struct cycliclist* list);

#endif