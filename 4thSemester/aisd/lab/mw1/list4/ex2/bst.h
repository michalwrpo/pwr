#ifndef BST_H
#define BST_H

#include <stdbool.h>

struct BST_Node {
    struct BST_Node* parent;
    long value;
    long height;
    struct BST_Node* left;
    struct BST_Node* right;
};

struct BST_Node* BST_insert(struct BST_Node* node, long value, long* comps, long* r, long* w, bool calc_height);

int BST_delete(struct BST_Node* node, long value, long* comps, long* r, long* w, bool calc_height);

unsigned int BST_height(struct BST_Node* node);

unsigned int max(unsigned int num1, unsigned int num2);

void BST_print(struct BST_Node* node);

#endif