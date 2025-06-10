#include <stdlib.h>
#include <stdio.h>

#include "binHeap.h"

int compare(int v1, int v2, long* comps) {
    (*comps)++;
    return v1 < v2;
}

BinomialHeap* makeHeap() {
    BinomialHeap* BH = malloc(sizeof(BinomialHeap));
    BH->head = NULL;
    return BH;
}

void heapLink(BHNode* root1, BHNode* root2) {
    root1->p = root2;
    root1->sibling = root2->child;
    root2->child = root1;
    root2->degree++;
}

BHNode* heapMerge(BinomialHeap* H1, BinomialHeap* H2) {
    BHNode *head, *N1, *N2, *N;

    N1 = H1->head;
    N2 = H2->head;

    if (N1 == NULL && N2 == NULL) {
        return NULL;
    } else if (N1 == NULL) {
        head = N2;
        N2 = N2->sibling;
    } else if (N2 == NULL) {
        head = N1;
        N1 = N1->sibling;
    } else if (N1->degree < N2->degree) {
        head = N1;
        N1 = N1->sibling;
    } else {
        head = N2;
        N2 = N2->sibling;
    }
    
    N = head;

    while (N1 != NULL && N2 != NULL) {
        if (N1->degree < N2->degree) {
            N->sibling = N1;
            N1 = N1->sibling;
        } else {
            N->sibling = N2;
            N2 = N2->sibling;
        }
        N = N->sibling;
    }

    while (N1 != NULL) {
        N->sibling = N1;
        N1 = N1->sibling;
        N = N->sibling;
    }
    
    while (N2 != NULL) {
        N->sibling = N2;
        N2 = N2->sibling;
        N = N->sibling;
    }
    
    return head;
}

void heapUnion(BinomialHeap* H, BinomialHeap* H1, long* comps) {    
    H->head = heapMerge(H, H1);

    free(H1);

    if (H->head == NULL) {
        return;
    }

    BHNode* prevx = NULL;
    BHNode* x = H->head;
    BHNode* nextx = x->sibling;

    while (nextx != NULL) {
        if (x->degree != nextx->degree || (nextx->sibling != NULL && nextx->sibling->degree == x->degree)) {
            prevx = x;
            x = nextx;
        } else if (compare(x->key, nextx->key, comps)) {
            x->sibling = nextx->sibling;
            heapLink(nextx, x);
        } else {
            if (prevx == NULL) {
                H->head = nextx;
            } else {
                prevx->sibling = nextx;
            }
            heapLink(x, nextx);
            x = nextx;
        }

        nextx = x->sibling;
    }
}

void heapInsert(BinomialHeap* H, int key, long* comps) {
    BinomialHeap* H1 = makeHeap();
    
    BHNode* x = malloc(sizeof(BHNode));
    x->key = key;
    x->degree = 0;
    x->p = NULL;
    x->child = NULL;
    x->sibling = NULL;

    H1->head = x;

    heapUnion(H, H1, comps);
}

BHNode* heapExtractMin(BinomialHeap* H, long* comps) {
    if (H == NULL || H->head == NULL)
        return 0;
    
    BHNode* N = H->head;
    BHNode* prev = NULL;
    BHNode* x = N;

    while(N->sibling != NULL) {
        if (compare(N->sibling->key, x->key, comps)) {
            prev = N;
            x = N->sibling;
        }
        N = N->sibling;
    }

    if (prev == NULL) {
        H->head = x->sibling;
    } else {
        prev->sibling = x->sibling;
    }
        
    if (x->child == NULL) 
        return x;
    
    prev = NULL;
    N = x->child;
    BHNode* next = N->sibling;
    
    while (next != NULL) {
        N->sibling = prev;
        
        prev = N;
        N = next;
        next = next->sibling;
    }
    
    N->sibling = prev;

    BinomialHeap* H1 = makeHeap();
    H1->head = N;

    heapUnion(H, H1, comps);

    return x;
}