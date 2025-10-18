#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "bfs.h"
#include "dfs.h"
#include "graph.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <algorithm>\n", argv[0]);
        fprintf(stderr, "Algorithms: bfs, dfs\n");
        return 1;
    }

    unsigned int algorithm = -1; // 0 - bfs, 1 - dfs

    if (strcmp(argv[1], "bfs") == 0) {
        algorithm = 0;
    } else if (strcmp(argv[1], "dfs") == 0) {
        algorithm = 1;
    } else {
        fprintf(stderr, "Unknown algorithm: %s\n", argv[1]);
        return 1;
    }

    struct dirent* dir;
    DIR* dfd;

    if ((dfd = opendir("./tests/1")) == NULL) {
        fprintf(stderr, "Can't open ./tests/1\n");
        return -1;
    }
    
    char buffer[64];
    graph* G = NULL;
    bool directed = false;
    unsigned int vertexNum = 0;
    unsigned int edgeNum = 0;

    while ((dir = readdir(dfd)) != NULL) {
        struct stat stbuf;

        char filename[] = "./tests/1/";
        strcat(filename, dir->d_name);

        if ((stat(filename, &stbuf)) == -1) {
            printf("Unable to stat file: %s\n", dir->d_name);
            continue;
        }

        if ((stbuf.st_mode & S_IFMT) != S_IFREG) {
            continue; // Not a regular file
        }

        FILE* file = fopen(filename, "r");
        printf("File: %s\n", dir->d_name);

        fscanf(file, "%s", buffer);
        
        if (strcmp(buffer, "D") == 0) {
            directed = true;
        } else if (strcmp(buffer, "U") == 0) {
            directed = false;
        } else {
            fprintf(stderr, "Invalid graph type in file %s\n", dir->d_name);
            fclose(file);
            continue;
        }

        printf("Graph type: %s\n", directed ? "Directed" : "Undirected");
        
        fscanf(file, "%s", buffer);
        vertexNum = (unsigned int)atoi(buffer);
        G = createGraph(vertexNum, directed);
        
        fscanf(file, "%s", buffer);
        edgeNum = (unsigned int)atoi(buffer);

        for (unsigned int i = 0; i < edgeNum; i++){
            unsigned int u, v;
            fscanf(file, "%u %u", &u, &v);
            addEdge(G, u - 1, v - 1);
        }

        fclose(file);

        if (algorithm == 0) {
            bfs(G, G->vertices[0]);

            for (unsigned int i = 0; i < G->vertexNum; i++) {
                vertex* v = G->vertices[i];
                printf("Vertex %u: distance = %d, parent = %d\n", v->number + 1, v->distance,
                    v->parent < (unsigned int)(-1) ? v->parent + 1 : (unsigned int)(-1));
            }
        } else if (algorithm == 1) {
            dfs(G);

            for (unsigned int i = 0; i < G->vertexNum; i++) {
                vertex* v = G->vertices[i];
                printf("Vertex %u: discovered = %d, returned = %d, parent = %d\n", v->number + 1, v->discoveryTime, v->returnTime,
                    v->parent < (unsigned int)(-1) ? v->parent + 1 : (unsigned int)(-1));
            }
        }
        
        freeGraph(G);
    }

    closedir(dfd);

    return 0;
}