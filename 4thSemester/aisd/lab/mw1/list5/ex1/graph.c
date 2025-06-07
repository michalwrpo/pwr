#include <time.h>
#include <stdbool.h>
#include <float.h>

#include "mtwister.h"

#include "graph.h"

void makeGraph(int vertexNum, double edges[vertexNum][vertexNum]) {
    MTRand r = seedRand(time(NULL));

    for (long i = 0; i < vertexNum; i++) {
        for (long j = 0; j < i; j++) {
            double rvalue = genRand(&r);
            edges[i][j] = rvalue;
            edges[j][i] = rvalue;
        }
        edges[i][i] = -1;
    }
}

void prim(int vertexNum, double edges[vertexNum][vertexNum], long parents[vertexNum]) {
    double keyValues[vertexNum];
    bool is_mst[vertexNum];
    int index;
    double minKey;

    for (long i = 0; i < vertexNum; i++) {
        parents[i] = -1;
        is_mst[i] = false;
        keyValues[i] = __DBL_MAX__;
    }

    keyValues[0] = 0;

    for (int i = 0; i < vertexNum; i++) {
        minKey = 2;
        for (int j = 0; j < vertexNum; j++) {
            if (is_mst[j])
                continue;

            if (keyValues[j] < minKey) {
                minKey = keyValues[j];
                index = j;
            }
        }

        is_mst[index] = true;

        for (int v = 0; v < vertexNum; v++) {
            if (!is_mst[v] && edges[index][v] < keyValues[v]) {
                keyValues[v] = edges[index][v];
                parents[v] = index;
            }
        }
    }
}