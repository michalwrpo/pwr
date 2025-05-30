#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

int max(int num1, int num2) {
    return num1 > num2 ? num1 : num2;
}

void BST_insert(struct BST* tree, long value) {
    struct BST_Node* y = NULL;
    struct BST_Node* x = tree->root;

    struct BST_Node* z = malloc(sizeof(struct BST_Node));
    z->value = value;
    z->left = NULL;
    z->right = NULL;
    
    while (x != NULL) {
        y = x;
        if (value < x->value) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == NULL) {
        tree->root = z;
    } else if (value < y->value) {
        y->left = z;
    } else {
        y->right = z;
    }
}

struct BST_Node* BST_search(struct BST_Node* node, long value) {
    while (node != NULL && value != node->value) {
        if (value < node->value) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return node;
}

struct BST_Node* BST_min(struct BST_Node* node) {
    while (node->left != NULL) 
        node = node->left;
    return node;
}

void transplant(struct BST* tree, struct BST_Node* u, struct BST_Node* v) {
    if (u->parent == NULL) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }

    if (v != NULL) {
        v->parent = u->parent;
    }
}

// deletes values from a tree
// returns -1 if the value isn't present
// or 0 if delete was successful
int BST_delete(struct BST* tree, long value) {
    struct BST_Node* node = BST_search(tree->root, value);
    if (node == NULL) 
        return -1;
    
    if (node->left == NULL) {
        transplant(tree, node, node->right);
    } else if (node->right == NULL) {
        transplant(tree, node, node->left);
    } else {
        struct BST_Node* y = BST_min(node->right);
        if (y->parent != node) {
            transplant(tree, y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        transplant(tree, node, y);
        y->left = node->left;
        y->left->parent = y;
    }
    free(node);
    return 0;
}

int BST_height(struct BST_Node* node) {
    if (node == NULL)
        return 0;
    
    return 1 + max(BST_height(node->left), BST_height(node->right));
}

void BST_print1(struct BST_Node* node, int depth, char prefix[4], char* lprefix, char* rprefix) {
    if (node == NULL)
        return;
    
    BST_print1(node->right, depth + 1, "⌈", lprefix, rprefix);
    
    if (prefix == NULL) {
        printf("%ld\n", node->value);
    } else {
        if (strcmp(prefix, "⌈") == 0) 
            lprefix[depth - 1] = '|';
        else if (strcmp(prefix, "⌊") == 0) 
            rprefix[depth - 1] = ' ';
        
        for (int i = 0; i < depth - 1; i++) {
            if (lprefix[i] == '|' || rprefix[i] == '|') {
                printf("| ");
            } else {
                printf("  ");
            }
        }

        printf("%s%ld\n", prefix, node->value);
    }

    lprefix[depth] = ' ';
    rprefix[depth] = '|';
    BST_print1(node->left, depth + 1, "⌊", lprefix, rprefix);

}

void BST_print(struct BST* tree) {
    if (tree == NULL) {
        return;
    }
    
    int h = BST_height(tree->root);

    char* lprefix = malloc(sizeof(char) * h);
    char* rprefix = malloc(sizeof(char) * h);

    for (int i = 0; i < h; i++) {
        lprefix[i] = ' ';
        rprefix[i] = ' ';
    }
    
    BST_print1(tree->root, 0, NULL, lprefix, rprefix);

    free(lprefix);
    free(rprefix);
}
