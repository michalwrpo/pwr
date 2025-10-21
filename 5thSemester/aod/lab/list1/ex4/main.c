#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/resource.h>

#include "graph.h"
#include "bipartite.h"

int main() {
    const rlim_t kStackSize = (unsigned long)(1 * 1024 * 1024) * 1024;   // min stack size = 1 GB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0) 
                fprintf(stderr, "setrlimit returned result = %d\n", result);
        }
    }

    struct dirent* dir;
    DIR* dfd;

    if ((dfd = opendir("./tests/4")) == NULL) {
        fprintf(stderr, "Can't open ./tests/4\n");
        return -1;
    }
    
    char buffer[64];
    graph* G = NULL;
    bool directed = false;
    unsigned int vertexNum = 0;
    unsigned int edgeNum = 0;

    while ((dir = readdir(dfd)) != NULL) {
        struct stat stbuf;

        char filename[] = "./tests/4/";
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

        bool bipartite = isBipartite(G);

        if (bipartite) {
            printf("The graph is bipartite.\n");
        } else {
            printf("The graph is not bipartite.\n");
        }

        if (!bipartite || vertexNum > 200) {
            freeGraph(G);
            continue;
        }

        unsigned int* whiteVertices = NULL;
        unsigned int* blackVertices = NULL;

        unsigned int whiteCount = 0;
        unsigned int blackCount = 0;

        split(G, &whiteVertices, &blackVertices, &whiteCount, &blackCount);

        printf("V0: ");
        for (unsigned int i = 0; i < whiteCount; i++) {
            printf("%u ", whiteVertices[i] + 1);
        }
        printf("\nV1: ");
        for (unsigned int i = 0; i < blackCount; i++) {
            printf("%u ", blackVertices[i] + 1);
        }
        printf("\n");

        free(whiteVertices);
        free(blackVertices);

        freeGraph(G);
    }

    closedir(dfd);

    return 0;
}