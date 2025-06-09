#include <stdlib.h>
#include <stdio.h>

#include "order.h"

int comp(int i, int j, int* weights) {
    return weights[i] > weights[j];
}

void copyArray(int* A, int* B, int iBegin, int iEnd) {
    for (int i = iBegin; i < iEnd; i++) {
        B[i] = A[i];
    }
}

void merge(int* B, int iBegin, int iMiddle, int iEnd, int* A, int* weights) {
    int i = iBegin, j = iMiddle;

    for (int k = iBegin; k < iEnd; k++) {
        if (i < iMiddle && (j >= iEnd || comp(A[i], A[j], weights))) {
            B[k] = A[i];
            i++;
        } else {
            B[k] = A[j];
            j++;
        }
    }
}

void splitMerge(int* B, int iBegin, int iEnd, int* A, int* weights) {
    if (iEnd - iBegin <= 1)
        return;

    int iMiddle = (iBegin + iEnd) >> 1;

    splitMerge(A, iBegin, iMiddle, B, weights);
    splitMerge(A, iMiddle, iEnd, B, weights);

    merge(B, iBegin, iMiddle, iEnd, A, weights);
}

void mergeSort(int* A, int* B, int n, int* weights) {
    copyArray(A, B, 0, n);
    splitMerge(A, 0, n, B, weights);
}

void count(int len, int** children, int* amount, int* weights, int i) {
    int cur = amount[i];
    if (cur == 0) {
        weights[i] = 0;
        return;
    }

    for (int j = 0; j < cur; j++) {
        if (weights[children[i][j]] == -1)
            count(len, children, amount, weights, children[i][j]);
    }

    int dummy[cur];
    mergeSort(children[i], dummy, cur, weights);

    for (int j = 0; j < cur; j++) {
        if (1 + j + weights[children[i][j]] > weights[i]) {
            weights[i] = 1 + j + weights[children[i][j]]; 
        }
    }
}

// returns list children of length n 
// where children[i] is either NULL
// when vertex i has no children or
// a sorted list of its children in
// order of which should get the signal first 
// total rounds is used to return the number
// of rounds needed to spread the signal
int** order(int* parents, int len, int* totalrounds) {
    int** children = malloc(len * sizeof(int*));    
    int amount[len];
    int filled[len];

    for (int i = 0; i < len; i++) {
        amount[i] = 0;
        filled[i] = 0;
    }

    for (int i = 0; i < len; i++) {
        if (parents[i] == -1)
            continue;
        
        amount[parents[i]]++;
    }
    
    int cur;

    for (int i = 0; i < len; i++) {
        cur = amount[i];
        // printf("%d: %d   ", i, cur);
        if (cur == 0) {
            children[i] = NULL;
        } else {
            children[i] = malloc(cur * sizeof(int));
            for (int j = 0; j < cur; j++) {
                children[i][j] = -1;
            }
        }
    }
    // printf("\n");

    for (int i = 0; i < len; i++) {
        cur = parents[i];
        if (cur == -1) 
            continue;

        children[cur][filled[cur]] = i;
        filled[cur]++;
    }

    int weights[len];

    for (int i = 0; i < len; i++) {
        weights[i] = -1;
    }
    
    for (int i = 0; i < len; i++) {
        if (parents[i] == -1) {
            count(len, children, amount, weights, i);    
            *totalrounds = weights[i];
            break;
        }        
    }

    
    // for (int i = 0; i < len; i++) {
    //     if (amount[i] < 3) 
    //         continue;
    //     printf("%d|%d: ", i, weights[i]);
    //     for (int j = 0; j < amount[i]; j++) {
    //         printf("%d|%d, ", children[i][j], weights[children[i][j]]);
    //     }
    //     printf("\n");
    // }

    return children;
}

