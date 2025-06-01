#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "splaytree.h"

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
void height_fixup(struct Splay_Node* node, long* r) {
    if (node == NULL)
        return;
    
    (*r)++;
    while (node->parent != NULL) { // read
        node = node->parent; // read
        if (node->left == NULL && node->right == NULL) { // double read
            node->height = 1;
        } else if (node->left == NULL) { // read
            node->height = 1 + node->right->height; // read
            (*r) += 2;
        } else if (node->right == NULL) { // read
            node->height = 1 + node->left->height; // read
            (*r) += 3;        
        } else {
            unsigned long h = 1 + max(node->left->height, node->right->height); // double read
            if (node->height == h)
                break;
            node->height = h;
            (*r) += 4;
        }
        (*r) += 3;
    }
}

void left_rotate(struct Splay_Tree* tree, struct Splay_Node* node, long* r, long* w, bool calc_height) {
    struct Splay_Node* y = node->right; // read

    if (y) {
        node->right = y->left; // read and write
        
        if (y->left != NULL) { // read
            y->left->parent = node; // read and write
            (*w)++;
            (*r)++;
        }

        y->parent = node->parent; // read and write

        (*w) += 2;
        (*r) += 3;
    }

    if (node->parent == NULL) { // read
        tree->root = y; // write
    } else if (node == node->parent->left) { // double read
        node->parent->left = y; // read and write
        (*r) += 3;
    } else {
        node->parent->right = y; // read and write
        (*r) += 3;
    }

    if (y != NULL) {
        y->left = node; // write
        (*w)++;
    }
    node->parent = y; // write

    (*w) += 2;
    (*r) += 2;

    if (calc_height) {
        height_fixup(node, r);
    }
}

void right_rotate(struct Splay_Tree* tree, struct Splay_Node* node, long* r, long* w, bool calc_height) {
    struct Splay_Node* y = node->left; // read

    if (y) {
        node->left = y->right; // read and write
        
        if (y->right != NULL) { // read
            y->right->parent = node; // read and write
            (*w)++;
            (*r)++;
        }

        y->parent = node->parent; // read and write

        (*w) += 2;
        (*r) += 3;
    }

    if (node->parent == NULL) { // read
        tree->root = y; // write
    } else if (node == node->parent->left) { // double read
        node->parent->left = y; // read and write
        (*r) += 3;
    } else {
        node->parent->right = y; // read and write
        (*r) += 3;
    }

    if (y != NULL) {
        y->right = node; // write
        (*w)++;
    }
    node->parent = y; // write

    (*w) += 2;
    (*r) += 2;

    if (calc_height) {
        height_fixup(node, r);
    }
}

void splay(struct Splay_Tree* tree, struct Splay_Node* node, long* r, long* w, bool calc_height) {
    if (node == NULL) 
        return;

    while (node->parent != NULL) { // read
        if (node->parent->parent == NULL) { // double read
            if (node->parent->left == node) { // double read
                right_rotate(tree, node->parent, r, w, calc_height); // read
            } else {
                left_rotate(tree, node->parent, r, w, calc_height); // read
            }
            (*r) += 3;
        } else if (node->parent->left == node && node->parent->parent->left == node->parent) { // sextuple read
            right_rotate(tree, node->parent->parent, r, w, calc_height); // double read
            right_rotate(tree, node->parent, r, w, calc_height); // read
            (*r) += 9;
        } else if (node->parent->right == node && node->parent->parent->right == node->parent) { // sextuple read
            left_rotate(tree, node->parent->parent, r, w, calc_height); // double read
            left_rotate(tree, node->parent, r, w, calc_height); // read
            (*r) += 15;
        } else if (node->parent->left == node && node->parent->parent->right == node->parent) { // sextuple read
            right_rotate(tree, node->parent, r, w, calc_height); // double read
            left_rotate(tree, node->parent, r, w, calc_height); // read
            (*r) += 21;
        } else { // sextuple read
            left_rotate(tree, node->parent, r, w, calc_height); // double read
            right_rotate(tree, node->parent, r, w, calc_height); // read
            (*r) += 21;
        }
        (*r) += 3;
    }
    (*r)++;
}

void Splay_insert(struct Splay_Tree* tree, long value, long* comps, long* r, long* w, bool calc_height) {
    struct Splay_Node* y = NULL; // read
    struct Splay_Node* x = tree->root; // read

    struct Splay_Node* z = malloc(sizeof(struct Splay_Node));
    z->value = value;
    z->height = 1;
    z->left = NULL; // read and write
    z->right = NULL; // read and write
    
    while (x != NULL) { // read
        y = x;
        if (compare(value, x->value, comps)) {
            x = x->left; // read
        } else {
            x = x->right; // read
        }
        (*r) += 2;
    }

    z->parent = y; // write

    if (y == NULL) { // read
        tree->root = z; // write
    } else if (compare(value, y->value, comps)) {
        y->left = z; // write
    } else {
        y->right = z; // write
    }

    (*w) += 4;
    (*r) += 6;

    splay(tree, z, r, w, calc_height);

    if (calc_height)
        height_fixup(z, r);

}

struct Splay_Node* Splay_search(struct Splay_Node* node, long value, long* comps, long *r) {
    while (node != NULL) {
        if (compare(value, node->value, comps)) {
            node = node->left; // read
        } else if (compare(node->value, value, comps)) {
            node = node->right; // read
        } else {
            return node;
        }
        (*r)++;
    }
    return NULL;
}

struct Splay_Node* Splay_min(struct Splay_Node* node, long* r) {
    while (node->left != NULL) { //  read
        node = node->left; // read
        (*r) += 2;
    }
    (*r)++;
    return node;
}

void transplant(struct Splay_Tree* tree, struct Splay_Node* u, struct Splay_Node* v, long* r, long* w, bool calc_height) {
    if (u == NULL) {
        return;
    }

    if (u->parent == NULL) { // read
        tree->root = v; // write
    } else if (u == u->parent->left) { // double read
        u->parent->left = v; // read and write
        (*r) += 3;
    } else {
        u->parent->right = v; // read and write
        (*r) += 3;
    }
    
    if (v != NULL) {
        v->parent = u->parent; // write
        (*w)++;        
    }
    

    if (calc_height) {
        if (v == NULL) {
            height_fixup(u->parent, r);
        } else {
            height_fixup(v, r);
        }
    }

    (*r)++;
    (*w)++;
}

// deletes values from a tree
// returns -1 if the value isn't present
// or 0 if delete was successful
int Splay_delete(struct Splay_Tree* tree, long value, long* comps, long* r, long* w, bool calc_height) {
    struct Splay_Node* z = Splay_search(tree->root, value, comps, r); // read
    if (z == NULL) 
        return -1;

    splay(tree, z, r, w, calc_height);
    
    struct Splay_Node* y;

    if (z->left == NULL) { // read
        transplant(tree, z, z->right, r, w, calc_height); // read
        (*r) += 2;        
    } else if (z->right == NULL) { //  read
        transplant(tree, z, z->left, r, w, calc_height); // read
        (*r) += 3;
    } else {
        y = Splay_min(z->right, r); // read

        if (y->parent != z) { // read
            transplant(tree, y, y->right, r, w, calc_height); // read
            y->right = z->right; // read and write
            y->right->parent = y; // read and write
            (*r) += 3;
            (*w) += 2;
        }
        transplant(tree, z, y, r, w, calc_height);
        y->left = z->left; // read and write
        y->left->parent = y; // read and write

        (*r) += 4;
        (*w) += 2;
    }

    free(z);

    (*r) += 3;

    return 0;
}


// deletes values from a tree
unsigned int Splay_height(struct Splay_Node* root) {
    if (root == NULL) {
        return 0;
    }
    
    return root->height;
}

void Splay_print1(struct Splay_Tree* tree, struct Splay_Node* node, int depth, char prefix[4], char* lprefix, char* rprefix) {
    if (node == NULL)
        return;
    
    Splay_print1(tree, node->right, depth + 1, "⌈", lprefix, rprefix);
    
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
    Splay_print1(tree, node->left, depth + 1, "⌊", lprefix, rprefix);

}

void Splay_print(struct Splay_Tree* tree) {
    if (tree == NULL) {
        return;
    }
    
    unsigned int h = Splay_height(tree->root);

    char* lprefix = malloc(sizeof(char) * h);
    char* rprefix = malloc(sizeof(char) * h);

    for (unsigned int i = 0; i < h; i++) {
        lprefix[i] = ' ';
        rprefix[i] = ' ';
    }
    
    Splay_print1(tree, tree->root, 0, NULL, lprefix, rprefix);

    free(lprefix);
    free(rprefix);
}
