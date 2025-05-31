#ifndef RBT_H
#define RBT_H

#include <stdbool.h>

struct RBT_Node {
    struct RBT_Node* parent;
    long value;
    long height;
    bool red;
    struct RBT_Node* left;
    struct RBT_Node* right;
};

struct RBT {
    struct RBT_Node* root;
    struct RBT_Node* nil;
};

void RBT_insert(struct RBT* tree, long value, long* comps, long* r, long* w, bool calc_height);

int RBT_delete(struct RBT* tree, long value, long* comps, long* r, long* w, bool calc_height);

unsigned int RBT_height(struct RBT_Node* node);

unsigned int max(unsigned int num1, unsigned int num2);

void RBT_print(struct RBT* tree);

#endif