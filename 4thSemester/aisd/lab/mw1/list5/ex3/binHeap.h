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
} BinomialHeap;

BinomialHeap* makeHeap();

void heapLink(BHNode* root1, BHNode* root2);
BHNode* heapMerge(BinomialHeap* H1, BinomialHeap* H2);
void heapUnion(BinomialHeap* H, BinomialHeap* H1, long* comps);

void heapInsert(BinomialHeap* H, int key, long* comps);

BHNode* heapExtractMin(BinomialHeap* H, long* comps);

#endif