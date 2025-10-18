#include <stdlib.h>

#include "graph.h"

graph* createGraph(unsigned int vertexNum, bool directed) {
    graph* G = (graph*)malloc(sizeof(graph));
    G->directed = directed;
    G->vertexNum = vertexNum;
    G->vertices = (vertex**)malloc(vertexNum * sizeof(vertex*));
    G->edgeNums = (unsigned int*)calloc(vertexNum, sizeof(unsigned int));
    G->edges = (unsigned int**)malloc(vertexNum * sizeof(unsigned int*));

    for (unsigned int i = 0; i < vertexNum; i++) {
        G->vertices[i] = (vertex*)malloc(sizeof(vertex));
        vertex* v = G->vertices[i];
        v->number = i;
        v->color = 0; // white
        v->distance = -1; // infinity
        v->parent = -1; // NIL
        v->discoveryTime = 0;
        v->returnTime = 0;
        G->edges[i] = NULL;
    }

    return G;
}

void addEdge(graph* G, unsigned int u, unsigned int v) {
    unsigned int edgeNum = G->edgeNums[u];
    G->edges[u] = (unsigned int*)realloc(G->edges[u], (edgeNum + 1) * sizeof(unsigned int));
    G->edges[u][edgeNum] = v;
    G->edgeNums[u]++;

    if (!G->directed) { 
        edgeNum = G->edgeNums[v];
        G->edges[v] = (unsigned int*)realloc(G->edges[v], (edgeNum + 1) * sizeof(unsigned int));
        G->edges[v][edgeNum] = u;
        G->edgeNums[v]++;
    }
}

void freeGraph(graph* G) {
    for (unsigned int i = 0; i < G->vertexNum; i++) {
        free(G->vertices[i]);
        free(G->edges[i]);
    }
    free(G->vertices);
    free(G->edgeNums);
    free(G->edges);
    free(G);
}