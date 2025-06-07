#include <time.h>
#include <stdbool.h>
#include <float.h>
#include <stdlib.h>

#include "mtwister.h"

#include "graph.h"

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

int compare(const void *a, const void *b) {
    double arg1 = (*(const edge**)a)->weight;
    double arg2 = (*(const edge**)b)->weight;
    return (arg1 > arg2) - (arg1 < arg2);
}

void kruskal(unsigned int vertexNum, edge* edges[vertexNum * (vertexNum - 1) >> 1], edge* result[vertexNum - 1]) {
    unsigned int size = vertexNum * (vertexNum - 1) >> 1;

    int parents[vertexNum];
    int rank[vertexNum];
    int k = 0; // edge counter

    for (unsigned int i = 0; i < vertexNum; i++) {
        parents[i] = i;
        rank[i] = 0;
    }
    
    qsort(edges, size, sizeof(edges[0]), compare);

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