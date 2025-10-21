#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct v {
    unsigned int number;
    unsigned char color; // 0 - no color, 1 - white, 2 - black
} vertex;

typedef struct g {
    bool directed;
    unsigned int vertexNum;
    vertex** vertices;
    unsigned int* edgeNums; 
    unsigned int** edges; // Adjacency list representation
} graph;

graph* createGraph(unsigned int vertexNum, bool directed);
void addEdge(graph* G, unsigned int u, unsigned int v);
void freeGraph(graph* G);
graph* reverseGraph(graph* G);  

#endif