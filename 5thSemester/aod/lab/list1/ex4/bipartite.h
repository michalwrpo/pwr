#ifndef BIPARTITE_H
#define BIPARTITE_H

#include <stdbool.h>

#include "graph.h"

bool isBipartite(graph* G);

// Works only if the graph already has assigned colors
void split(graph* G, unsigned int** whiteVertices, unsigned int** blackVertices, unsigned int* whiteCount, unsigned int* blackCount);

#endif