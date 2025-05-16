#ifndef BST_H
#define BST_H

struct BST_Node {
    struct BST_Node* parent;
    long value;
    struct BST_Node* left;
    struct BST_Node* right;
};

struct BST_Node* BST_insert(struct BST_Node* node, long value);

int BST_delete(struct BST_Node* node, long value);

int BST_height(struct BST_Node* node);

void BST_print(struct BST_Node* node);

#endif