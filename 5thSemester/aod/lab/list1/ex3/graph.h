#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct v {
    unsigned int number;
    unsigned char color; // 0 - white, 1 - gray, 2 - black
    int distance;
    unsigned int parent;
    unsigned int discoveryTime;
    unsigned int returnTime;
} vertex;

typedef struct g {
    bool directed;
    unsigned int vertexNum;
    vertex** vertices;
    unsigned int* edgeNums; 
    unsigned int** edges; // Adjacency list representation
    unsigned int* order;
    unsigned int** sccs;
    unsigned int* sccSizes;
    unsigned int sccCount;
} graph;

graph* createGraph(unsigned int vertexNum, bool directed);
void addEdge(graph* G, unsigned int u, unsigned int v);
void freeGraph(graph* G);
graph* reverseGraph(graph* G);  

#endif