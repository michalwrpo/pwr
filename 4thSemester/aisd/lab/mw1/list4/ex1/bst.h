#ifndef BST_H
#define BST_H

struct BST_Node {
    struct BST_Node* parent;
    long value;
    struct BST_Node* left;
    struct BST_Node* right;
};

struct BST {
    struct BST_Node* root;
};

void BST_insert(struct BST* tree, long value);

int BST_delete(struct BST* tree, long value);

int BST_height(struct BST_Node* root);

void BST_print(struct BST* tree);

#endif