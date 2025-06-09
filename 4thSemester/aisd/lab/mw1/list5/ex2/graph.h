#ifndef GRAPH_H
#define GRAPH_H

typedef struct e {
    int vertex1;
    int vertex2;
    double weight; 
} edge;

void makeGraph(unsigned int vertexNum, double edges[vertexNum][vertexNum]);
void makeGraphList(unsigned int vertexNum, edge* edges[vertexNum * (vertexNum - 1) >> 1]);

void prim(unsigned int vertexNum, double edges[vertexNum][vertexNum], int parents[vertexNum]);
void kruskal(unsigned int vertexNum, edge* edges[vertexNum * (vertexNum - 1) >> 1], edge* result[vertexNum - 1]);

#endif