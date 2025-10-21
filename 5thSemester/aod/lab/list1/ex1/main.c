#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "bfs.h"
#include "dfs.h"
#include "graph.h"

void dfsPrint(graph* G, vertex* u, unsigned int* depth) {
    u->color = 1; // gray

    for (unsigned int i = 0; i < G->edgeNums[u->number]; i++) {
        unsigned int vNum = G->edges[u->number][i];
        vertex* v = G->vertices[vNum];
        if (v->parent == u->number) {
            for (unsigned int i = 0; i < depth[v->number] - 1; i++) {
                printf(" ");
            }
            
            printf("∟%u\n", v->number + 1);
            dfsPrint(G, v, depth);
        }
    }

    u->color = 2; // black
}

void run(FILE* file, char* filename, unsigned int algorithm, bool tree) {
    char buffer[64];
    graph* G = NULL;
    bool directed = false;
    unsigned int vertexNum = 0;
    unsigned int edgeNum = 0;

    fscanf(file, "%s", buffer);
    
    if (strcmp(buffer, "D") == 0) {
        directed = true;
    } else if (strcmp(buffer, "U") == 0) {
        directed = false;
    } else {
        fprintf(stderr, "Invalid graph type in file %s\n", filename);
        fclose(file);
        return;
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

    if (algorithm == 0) {
        bfs(G, G->vertices[0]);
    } else if (algorithm == 1) {
        dfs(G);
    }

    for (unsigned int i = 0; i < G->vertexNum; i++) {
        printf("%u ", G->order[i] + 1);
    }
    printf("\n");

    if (!tree) {
        freeGraph(G);
        return;
    }

    unsigned int depth[vertexNum];
    depth[G->order[0]] = 0;
    for (unsigned int i = 1; i < vertexNum; i++) {
        unsigned int v = G->order[i];
        unsigned int parent = G->vertices[v]->parent;
        depth[v] = depth[parent] + 1;
    }

    printf("%u\n", G->vertices[depth[G->order[0]]]->number + 1);

    for (unsigned int i = 0; i < G->vertexNum; i++) {
        G->vertices[i]->color = 0; // white
    }

    for (unsigned int i = 0; i < G->vertexNum; i++) {
        vertex* v = G->vertices[i];
        if (v->color == 0) { // white
            dfsPrint(G, v, depth);
        }
    }
    
    freeGraph(G);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <algorithm> [tree] [file]\n", argv[0]);
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

    if (argc < 4) {
        bool tree = false;
        if (argc == 3 && strcmp(argv[2], "tree") == 0) {
            tree = true;
        }

        struct dirent* dir;
        DIR* dfd;
    
        if ((dfd = opendir("./tests/1")) == NULL) {
            fprintf(stderr, "Can't open ./tests/1\n");
            return -1;
        }
    
        while ((dir = readdir(dfd)) != NULL) {
            struct stat stbuf;
    
            char filename[256];
            snprintf(filename, sizeof(filename), "./tests/1/%s", dir->d_name);
    
            if ((stat(filename, &stbuf)) == -1) {
                printf("Unable to stat file: %s\n", dir->d_name);
                continue;
            }
    
            if ((stbuf.st_mode & S_IFMT) != S_IFREG) {
                continue; // Not a regular file
            }
    
            FILE* file = fopen(filename, "r");
            printf("File: %s\n", filename);
    
            run(file, filename, algorithm, tree);
            fclose(file);
        }
    
        closedir(dfd);
    } else if (argc == 4) {
        bool tree = (strcmp(argv[2], "tree") == 0) ?  true : false;
        
        FILE* file = fopen(argv[3], "r");
        if (file == NULL) {
            fprintf(stderr, "Unable to open file: %s\n", argv[3]);
            return 1;
        }
        
        run(file, argv[3], algorithm, tree);
        fclose(file);
    }
    

    return 0;
}