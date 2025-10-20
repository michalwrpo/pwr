#include <stdbool.h>
#include <stdlib.h>

#include "scc.h"

void dfsVisit(graph* G, vertex* u, unsigned int* time, unsigned int* index, bool recordSCC) {
    (*time)++;
    u->discoveryTime = *time;
    u->color = 1; // gray

    if (recordSCC) {
        unsigned int sccIndex = G->sccCount - 1;
        unsigned int sccSize = G->sccSizes[sccIndex];
        G->sccs[sccIndex] = (unsigned int*)realloc(G->sccs[sccIndex], (sccSize + 1) * sizeof(unsigned int));
        G->sccs[sccIndex][sccSize] = u->number;
        G->sccSizes[sccIndex]++;
    }
    
    for (unsigned int i = 0; i < G->edgeNums[u->number]; i++) {
        unsigned int vNum = G->edges[u->number][i];
        vertex* v = G->vertices[vNum];
        if (v->color == 0) { // white
            v->parent = u->number;
            dfsVisit(G, v, time, index, recordSCC);
        }
    }
    
    u->color = 2; // black
    G->order[(*index)--] = u->number;
    (*time)++;
    u->returnTime = *time;
}

void findSCCs(graph* G) {
    for (unsigned int i = 0; i < G->vertexNum; i++) {
        vertex* v = G->vertices[i];
        v->color = 0; // white
        v->parent = -1; // NIL
    }

    unsigned int time = 0;
    unsigned int index = G->vertexNum - 1;

    for (unsigned int i = 0; i < G->vertexNum; i++) {
        vertex* v = G->vertices[i];
        if (v->color == 0) { // white
            dfsVisit(G, v, &time, &index, false);
        }
    }


    graph* revG = reverseGraph(G);

    for (unsigned int i = 0; i < revG->vertexNum; i++) {
        vertex* v = revG->vertices[i];
        v->color = 0; // white
        v->parent = -1; // NIL
    }

    time = 0;
    index = revG->vertexNum - 1;
    revG->sccCount = 0;
    revG->sccs = (unsigned int**)NULL;
    revG->sccSizes = (unsigned int*)NULL;


    for (unsigned int i = 0; i < revG->vertexNum; i++) {
        unsigned int vNum = G->order[i];
        vertex* v = revG->vertices[vNum];
        if (v->color == 0) { // white
            revG->sccCount++;
            revG->sccs = (unsigned int**)realloc(revG->sccs, revG->sccCount * sizeof(unsigned int*));
            revG->sccs[revG->sccCount - 1] = NULL;
            revG->sccSizes = (unsigned int*)realloc(revG->sccSizes, revG->sccCount * sizeof(unsigned int));
            revG->sccSizes[revG->sccCount - 1] = 0;

            dfsVisit(revG, v, &time, &index, true);
        }
    }
    
    G->sccCount = revG->sccCount;
    G->sccSizes = (unsigned int*)malloc(G->sccCount * sizeof(unsigned int));
    G->sccs = (unsigned int**)malloc(G->sccCount * sizeof(unsigned int*));

    for (unsigned int i = 0; i < G->sccCount; i++) {
        G->sccSizes[i] = revG->sccSizes[i];
        G->sccs[i] = (unsigned int*)malloc(G->sccSizes[i] * sizeof(unsigned int));
        for (unsigned int j = 0; j < G->sccSizes[i]; j++) {
            G->sccs[i][j] = revG->sccs[i][j];
        }
    } 

    freeGraph(revG);
}

