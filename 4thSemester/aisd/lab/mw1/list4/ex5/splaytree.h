#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <stdbool.h>

struct Splay_Node {
    struct Splay_Node* parent;
    long value;
    unsigned long height;
    struct Splay_Node* left;
    struct Splay_Node* right;
};

struct Splay_Tree {
    struct Splay_Node* root;
};

void Splay_insert(struct Splay_Tree* tree, long value, long* comps, long* r, long* w, bool calc_height);

int Splay_delete(struct Splay_Tree* tree, long value, long* comps, long* r, long* w, bool calc_height);

unsigned int Splay_height(struct Splay_Node* node);

unsigned int max(unsigned int num1, unsigned int num2);

void Splay_print(struct Splay_Tree* tree);

#endif