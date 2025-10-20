#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "graph.h"
#include "topological_sort.h"

int main() {
    struct dirent* dir;
    DIR* dfd;

    if ((dfd = opendir("./tests/2")) == NULL) {
        fprintf(stderr, "Can't open ./tests/2\n");
        return -1;
    }
    
    char buffer[64];
    graph* G = NULL;
    bool directed = false;
    unsigned int vertexNum = 0;
    unsigned int edgeNum = 0;

    while ((dir = readdir(dfd)) != NULL) {
        struct stat stbuf;

        char filename[] = "./tests/2/";
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
        } else {
            fprintf(stderr, "Invalid graph type in file %s\n", dir->d_name);
            fclose(file);
            continue;
        }
        
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

        topologicalSort(G);

        if (G->order[vertexNum - 1] == vertexNum) {
            printf("Graph has a directed cycle.\n");
        } else {
            printf("Graph does not have a directed cycle.\n");
            if (G->vertexNum <= 200) {
                printf("Topological order: ");
                for (unsigned int i = 0; i < vertexNum; i++) {
                    printf("%u ", G->order[i] + 1);
                }
                printf("\n");
            }
        }


        freeGraph(G);
    }

    closedir(dfd);

    return 0;
}