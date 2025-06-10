#include <time.h>
#include <stdbool.h>
#include <float.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "mtwister.h"

#include "graph.h"

void swap(edge** A, int i, int j) {
    edge* temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

int partition(edge** A, int s, int e) {
    float pivot = A[e]->weight;
    int i = s;

    for (int j = s; j < e; j++) {
        if (A[j]->weight <= pivot) {
            swap(A, i, j);
            i++;
        }
    }

    swap(A, i, e);
    return i;
}

void quicksort(edge** A, int s, int e) {
    if (s >= e || s < 0)
        return;

    int p = partition(A, s, e);

    quicksort(A, s, p - 1);
    quicksort(A, p + 1, e);    
}

void makeGraph(unsigned int vertexNum, double edges[vertexNum][vertexNum]) {
    MTRand r = seedRand(time(NULL));

    for (unsigned int i = 0; i < vertexNum; i++) {
        for (unsigned int j = 0; j < i; j++) {
            double rvalue = genRand(&r);
            edges[i][j] = rvalue;
            edges[j][i] = rvalue;
        }
        edges[i][i] = -1;
    }
}

void makeGraphList(unsigned int vertexNum, edge* edges[vertexNum * (vertexNum - 1) >> 1]) {
    MTRand r = seedRand(time(NULL));

    int k = 0;
    for (unsigned int i = 1; i < vertexNum; i++) {
        for (unsigned int j = 0; j < i; j++) {
            double rvalue = genRand(&r);
            edge* e = malloc(sizeof(edge));
            e->vertex1 = j;
            e->vertex2 = i;
            e->weight = rvalue;
            edges[k] = e;
            k++;
        }
    }
}

void prim(unsigned int vertexNum, double edges[vertexNum][vertexNum], int parents[vertexNum]) {
    double keyValues[vertexNum];
    bool is_mst[vertexNum];
    int index;
    double minKey;

    for (unsigned int i = 0; i < vertexNum; i++) {
        parents[i] = -1;
        is_mst[i] = false;
        keyValues[i] = __DBL_MAX__;
    }

    keyValues[0] = 0;

    for (unsigned int i = 0; i < vertexNum; i++) {
        minKey = 2;
        for (unsigned int j = 0; j < vertexNum; j++) {
            if (is_mst[j])
                continue;

            if (keyValues[j] < minKey) {
                minKey = keyValues[j];
                index = j;
            }
        }

        is_mst[index] = true;

        for (unsigned int v = 0; v < vertexNum; v++) {
            if (!is_mst[v] && edges[index][v] < keyValues[v]) {
                keyValues[v] = edges[index][v];
                parents[v] = index;
            }
        }
    }
}

int find(int* parents, int i) {
    if (parents[i] == i) {
        return i;
    }
    return find(parents, parents[i]);
}

void treeUnion(int* parents, int* rank, int x, int y) {
    int xroot = find(parents, x);
    int yroot = find(parents, y);
    if (rank[xroot] < rank[yroot]) {
        parents[xroot] = yroot;
    } else if (rank[yroot] < rank[xroot]) {
        parents[yroot] = xroot;
    } else {
        parents[yroot] = xroot;
        rank[xroot]++;
    }
}

void kruskal(unsigned int vertexNum, edge* edges[vertexNum * (vertexNum - 1) >> 1], edge* result[vertexNum - 1], int print) {
    unsigned int size = vertexNum * (vertexNum - 1) >> 1;

    int parents[vertexNum];
    int rank[vertexNum];
    int k = 0; // edge counter

    for (unsigned int i = 0; i < vertexNum; i++) {
        parents[i] = i;
        rank[i] = 0;
    }
    
    quicksort(edges, 0, size - 1);

    if (print) {
        printf("Sorted edges:\n");
        for (unsigned int i = 0; i < size; i++) {
            printf("(%d, %d, %.2f) ", edges[i]->vertex1, edges[i]->vertex2, edges[i]->weight);
        }
        printf("\n");
    }
    

    for (unsigned int i = 0; i < size; i++) {
        edge* e = edges[i]; 
        int u = e->vertex1;
        int v = e->vertex2;

        int x = find(parents, u);
        int y = find(parents, v);
        
        if (x != y) {
            result[k] = e;
            treeUnion(parents, rank, x, y);
            k++;
        }
    }
}