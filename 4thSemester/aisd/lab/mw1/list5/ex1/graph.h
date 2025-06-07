#ifndef GRAPH_H
#define GRAPH_H

void makeGraph(int vertexNum, double edges[vertexNum][vertexNum]);

void prim(int vertexNum, double edges[vertexNum][vertexNum], long parents[vertexNum]);

#endif