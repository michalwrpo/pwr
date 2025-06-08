#ifndef BINHEAP_H
#define BINHEAP_H

typedef struct BinHeapNode {
    int key;
    int degree;
    struct BinHeapNode* p;
    struct BinHeapNode* child;
    struct BinHeapNode* sibling;
} BHNode;

typedef struct BinHeap {
    BHNode* head;
} BinaryHeap;

BinaryHeap* makeHeap();

void heapLink(BHNode* root1, BHNode* root2);
BHNode* heapMerge(BinaryHeap* H1, BinaryHeap* H2);
void heapUnion(BinaryHeap* H, BinaryHeap* H1, long* comps);

void heapInsert(BinaryHeap* H, int key, long* comps);

BHNode* heapExtractMin(BinaryHeap* H, long* comps);

#endif