#include <stdlib.h>

#include "bipartite.h"

bool isBipartite(graph* G) {
    for (unsigned int i = 0; i < G->vertexNum; i++) {
        G->vertices[i]->color = 0; // no color
    }

    for (unsigned int i = 0; i < G->vertexNum; i++) {
        if (G->vertices[i]->color != 0) {
            continue;
        }

        G->vertices[i]->color = 1; // white
        unsigned int* queue = (unsigned int*)malloc(G->vertexNum * sizeof(unsigned int));
        unsigned int front = 0, back = 0;
        queue[back++] = i;

        while (front < back) {
            unsigned int u = queue[front++];
            unsigned char currentColor = G->vertices[u]->color;
            unsigned char neighborColor = (currentColor == 1) ? 2 : 1; // alternate color

            for (unsigned int i = 0; i < G->edgeNums[u]; i++) {
                unsigned int v = G->edges[u][i];
                if (G->vertices[v]->color == 0) {
                    G->vertices[v]->color = neighborColor;
                    queue[back++] = v;
                } else if (G->vertices[v]->color == currentColor) {
                    free(queue);
                    return false; // same color found on adjacent vertices
                }
            }
        }

        free(queue);
    }

    return true;
}

void split(graph* G, unsigned int** whiteVertices, unsigned int** blackVertices, unsigned int* whiteCount, unsigned int* blackCount) {
    *whiteCount = 0;
    *blackCount = 0;

    for (unsigned int i = 0; i < G->vertexNum; i++) {
        if (G->vertices[i]->color == 1) { // white
            (*whiteCount)++;
        } else if (G->vertices[i]->color == 2) { // black
            (*blackCount)++;
        }
    }

    *whiteVertices = (unsigned int*)malloc((*whiteCount) * sizeof(unsigned int));
    *blackVertices = (unsigned int*)malloc((*blackCount) * sizeof(unsigned int));

    unsigned int wIndex = 0, bIndex = 0;
    for (unsigned int i = 0; i < G->vertexNum; i++) {
        if (G->vertices[i]->color == 1) { // white
            (*whiteVertices)[wIndex++] = G->vertices[i]->number;
        } else if (G->vertices[i]->color == 2) { // black
            (*blackVertices)[bIndex++] = G->vertices[i]->number;
        }
    }
}