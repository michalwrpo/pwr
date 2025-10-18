#include "dfs.h"

void dfsVisit(graph* G, vertex* u, unsigned int* time, unsigned int* index) {
    (*time)++;
    u->discoveryTime = *time;
    u->color = 1; // gray
    G->order[(*index)++] = u->number;

    for (unsigned int i = 0; i < G->edgeNums[u->number]; i++) {
        unsigned int vNum = G->edges[u->number][i];
        vertex* v = G->vertices[vNum];
        if (v->color == 0) { // white
            v->parent = u->number;
            dfsVisit(G, v, time, index);
        }
    }

    u->color = 2; // black
    (*time)++;
    u->returnTime = *time;
}

void dfs(graph* G) {
    for (unsigned int i = 0; i < G->vertexNum; i++) {
        vertex* v = G->vertices[i];
        v->color = 0; // white
        v->parent = -1; // NIL
    }

    unsigned int time = 0;
    unsigned int index = 0;

    for (unsigned int i = 0; i < G->vertexNum; i++) {
        vertex* v = G->vertices[i];
        if (v->color == 0) { // white
            dfsVisit(G, v, &time, &index);
        }
    }
}
