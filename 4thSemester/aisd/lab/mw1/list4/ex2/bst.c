#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "bst.h"

unsigned int max(unsigned int num1, unsigned int num2) {
    return num1 > num2 ? num1 : num2;
}

bool compare(int v1, int v2, long* comps) {
    (*comps)++;
    return v1 < v2;
}

bool compare_equal(int v1, int v2, long* comps) {
    (*comps)++;
    return v1 == v2;
}

// fixes height of every node above the given one
void height_fixup(struct BST_Node* node, long* r) {
    (*r)++;
    while (node->parent != NULL) {
        node = node->parent;
        (*r)++;        
        if (node->left == NULL && node->right == NULL) {
            node->height = 1;
        } else if (node->left == NULL) {
            node->height = 1 + node->right->height;
        } else if (node->right == NULL) {
            (*r)++;        
            node->height = 1 + node->left->height;
        } else {
            (*r)++;        
            if (node->height == 1 + max(node->left->height, node->right->height))
                break;
            node->height = 1 + max(node->left->height, node->right->height);
        }
    }
}

void BST_insert(struct BST* tree, long value, long* comps, long* r, long* w, bool calc_height) {
    struct BST_Node* y = NULL;

    struct BST_Node* x = tree->root; // read
    (*r)++;

    struct BST_Node* z = malloc(sizeof(struct BST_Node));
    z->value = value;
    z->height = 0;
    z->left = NULL; // write
    z->right = NULL; // write
    
    while (x != NULL) {
        y = x;
        if (compare(value, x->value, comps)) {
            x = x->left; // read
        } else {
            x = x->right; // read
        }
        (*r)++;
    }

    z->parent = y; // write
    if (y == NULL) {
        tree->root = z; // write
    } else if (compare(value, y->value, comps)) {
        y->left = z; // write
    } else {
        y->right = z; // write
    }

    (*w) += 4;

    if (calc_height)
        height_fixup(z, r);
}

struct BST_Node* BST_search(struct BST_Node* node, long value, long* comps, long *r) {
    while (node != NULL && value != node->value) {
        if (compare(value, node->value, comps)) {
            node = node->left; // read
        } else {
            node = node->right; // read
        }
        (*r)++;
    }
    return node;
}

struct BST_Node* BST_min(struct BST_Node* node, long* r) {
    (*r)++;
    while (node->left != NULL) { // read
        node = node->left; // read
        (*r) += 2;
    }
    return node;
}

void transplant(struct BST* tree, struct BST_Node* u, struct BST_Node* v, long* r, long* w) {
    (*r)++;
    if (u->parent == NULL) { // read
        tree->root = v; // write
    } else if (u == u->parent->left) { // double read
        (*r) += 3;
        u->parent->left = v; // read and write
    } else {
        (*r) += 3;
        u->parent->right = v; // read and write
    }
    (*w)++;
    
    if (v != NULL) {
        v->height = u->height;
        v->parent = u->parent; // write
        (*w)++;
    }
}

// deletes values from a tree
// returns -1 if the value isn't present
// or 0 if delete was successful
int BST_delete(struct BST* tree, long value, long* comps, long* r, long* w, bool calc_height) {
    (*r)++;
    struct BST_Node* node = BST_search(tree->root, value, comps, r); // read
    if (node == NULL) 
        return -1;
    
    (*r) += 2;
    if (node->left == NULL) { // read
        transplant(tree, node, node->right, r, w); // read
        
        if (calc_height)
            height_fixup(node, r);
    } else if (node->right == NULL) { // read
        (*r)++;
        transplant(tree, node, node->left, r, w); // read

        if (calc_height)
            height_fixup(node, r);
    } else {
        struct BST_Node* y = BST_min(node->right, r); // read
        if (y->parent != node) { // read
            transplant(tree, y, y->right, r, w); // read
            y->right = node->right; // read and write
            y->right->parent = y; // read and write
        }
        transplant(tree, node, y, r, w);
        y->left = node->left; // read and write
        y->left->parent = y; // read and write

        (*r) += 7;
        (*w) += 4;

        if (calc_height)
            height_fixup(y, r);
    }
    free(node);
    return 0;
}


// deletes values from a tree
unsigned int BST_height(struct BST_Node* root) {
    if (root == NULL)
        return 0;
    
    return root->height;
}

void BST_print1(struct BST_Node* node, int depth, char prefix[4], char* lprefix, char* rprefix) {
    if (node == NULL)
        return;
    
    BST_print1(node->right, depth + 1, "⌈", lprefix, rprefix);
    
    if (prefix == NULL) {
        printf("%ld%ld\n", node->value, node->height);
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

        printf("%s%ld%ld\n", prefix, node->value, node->height);
    }

    lprefix[depth] = ' ';
    rprefix[depth] = '|';
    BST_print1(node->left, depth + 1, "⌊", lprefix, rprefix);

}

void BST_print(struct BST* tree) {
    if (tree == NULL) {
        return;
    }
    
    unsigned int h = BST_height(tree->root);

    char* lprefix = malloc(sizeof(char) * h);
    char* rprefix = malloc(sizeof(char) * h);

    for (unsigned int i = 0; i < h; i++) {
        lprefix[i] = ' ';
        rprefix[i] = ' ';
    }
    
    BST_print1(tree->root, 0, NULL, lprefix, rprefix);

    free(lprefix);
    free(rprefix);
}
