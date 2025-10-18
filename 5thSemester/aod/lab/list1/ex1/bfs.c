#include "bfs.h"

void bfs(graph* G, vertex* s) {
    for (unsigned int i = 0; i < G->vertexNum; i++) {
        vertex* v = G->vertices[i];
        v->color = 0; // white
        v->distance = -1; // infinity
        v->parent = -1; // NIL
    }

    s->color = 1; // gray
    s->distance = 0;
    s->parent = -1; // NIL

    vertex* queue[G->vertexNum];
    unsigned int front = 0;
    unsigned int back = 0;

    queue[back++] = s;

    while (front < back) {
        vertex* u = queue[front++];
        for (unsigned int i = 0; i < G->edgeNums[u->number]; i++) {
            unsigned int vNum = G->edges[u->number][i];
            vertex* v = G->vertices[vNum];
            if (v->color == 0) { // white
                v->color = 1; // gray
                v->distance = u->distance + 1;
                v->parent = u->number;
                queue[back++] = v;
            }
        }
        u->color = 2; // black
    }
}

