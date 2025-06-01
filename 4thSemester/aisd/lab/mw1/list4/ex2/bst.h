#ifndef BST_H
#define BST_H

#include <stdbool.h>

struct BST_Node {
    struct BST_Node* parent;
    long value;
    unsigned long height;
    struct BST_Node* left;
    struct BST_Node* right;
};

struct BST {
    struct BST_Node* root;
};

void BST_insert(struct BST* tree, long value, long* comps, long* r, long* w, bool calc_height);

int BST_delete(struct BST* tree, long value, long* comps, long* r, long* w, bool calc_height);

unsigned int BST_height(struct BST_Node* node);

unsigned int max(unsigned int num1, unsigned int num2);

void BST_print(struct BST* tree);

#endif