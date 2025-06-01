#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "rbt.h"

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

// fixes height of the given node and every node above it
void height_fixup(struct RBT* tree, struct RBT_Node* node, long* r) {
    tree->nil->height = 0; // read
    while (node != tree->nil) { // read
        node->height = 1 + max(node->left->height, node->right->height); // double read
        node = node->parent; // read
        (*r) += 4;
    }
    (*r) += 2;
}

void left_rotate(struct RBT* tree, struct RBT_Node* node, long* r, long* w, bool calc_height) {
    struct RBT_Node* y = node->right; // read
    node->right = y->left; // read and write
    
    if (y->left != tree->nil) { // double read
        y->left->parent = node; // read and write
        (*w)++;
        (*r)++;
    }

    y->parent = node->parent; // read and write

    if (node->parent == tree->nil) { // read
        tree->root = y; // write
        (*w)++;
    } else if (node == node->parent->left) { // double read
        node->parent->left = y; // read and write
        (*r) += 3;
    } else {
        node->parent->right = y; // read and write
        (*r) += 3;
    }

    y->left = node; // write
    node->parent = y; // write

    (*w) += 5;
    (*r) += 6;

    if (calc_height) {
        height_fixup(tree, node, r);
    }
}

void right_rotate(struct RBT* tree, struct RBT_Node* node, long* r, long* w, bool calc_height) {
    struct RBT_Node* y = node->left; // read
    node->left = y->right; // read and write
    
    if (y->right != tree->nil) { // double read
        y->right->parent = node; // read and write
        (*w)++;
        (*r)++;
    }

    y->parent = node->parent; // read and write

    if (node->parent == tree->nil) { // read
        tree->root = y; // write
        (*w)++;
    } else if (node == node->parent->left) { // double read
        node->parent->left = y; // read and write
        (*r) += 3;
    } else {
        node->parent->right = y; // read and write
        (*r) += 3;
    }

    y->right = node; // write
    node->parent = y; // write

    (*w) += 5;
    (*r) += 6;

    if (calc_height) {
        height_fixup(tree, node, r);
    }
}

void RBT_insert_fixup(struct RBT* tree, struct RBT_Node* node, long* r, long* w, bool calc_height) {
    while (node->parent->red) { // read
        struct RBT_Node* y;
        if (node->parent == node->parent->parent->left) { // quadruple read
            y = node->parent->parent->right; // triple read
            if (y->red) {
                node->parent->red = false;
                y->red = false;
                node->parent->parent->red = true; // double read
                node = node->parent->parent; // double read
                (*r) += 4;
            } else {
                if (node == node->parent->right) { // double read
                    node = node->parent; // read
                    left_rotate(tree, node, r, w, calc_height);
                    (*r)++;
                }
                node->parent->red = false; // read
                node->parent->parent->red = true; //double read
                right_rotate(tree, node->parent->parent, r, w, calc_height); // double read
                (*r) += 7;
            }
            (*r) += 3;
        } else {
            y = node->parent->parent->left; // triple read
            if (y->red) {
                node->parent->red = false;
                y->red = false;
                node->parent->parent->red = true; // double read
                node = node->parent->parent; // double read
                (*r) += 4;
            } else {
                if (node == node->parent->left) { // double read
                    node = node->parent; // read
                    right_rotate(tree, node, r, w, calc_height);
                    (*r)++;
                }
                node->parent->red = false; // read
                node->parent->parent->red = true; //double read
                left_rotate(tree, node->parent->parent, r, w, calc_height); // double read
                (*r) += 7;
            }
            (*r) += 3;
        }
        (*r) += 5;
    }
    tree->root->red = false; // read
    (*r) += 2;
}

void RBT_insert(struct RBT* tree, long value, long* comps, long* r, long* w, bool calc_height) {
    struct RBT_Node* y = tree->nil; // read
    struct RBT_Node* x = tree->root; // read

    struct RBT_Node* z = malloc(sizeof(struct RBT_Node));
    z->value = value;
    z->height = 0;
    z->red = true;
    z->left = tree->nil; // read and write
    z->right = tree->nil; // read and write
    
    while (x != tree->nil) { // read
        y = x;
        if (compare(value, x->value, comps)) {
            x = x->left; // read
        } else {
            x = x->right; // read
        }
        (*r) += 2;
    }

    z->parent = y; // write
    if (y == tree->nil) { // read
        tree->root = z; // write
    } else if (compare(value, y->value, comps)) {
        y->left = z; // write
    } else {
        y->right = z; // write
    }

    (*w) += 4;
    (*r) += 6;

    if (calc_height)
        height_fixup(tree, z, r);

    RBT_insert_fixup(tree, z, r, w, calc_height);
}

struct RBT_Node* RBT_search(struct RBT* tree, struct RBT_Node* node, long value, long* comps, long *r) {
    while (node != tree->nil && value != node->value) {
        if (compare(value, node->value, comps)) {
            node = node->left; // read
        } else {
            node = node->right; // read
        }
        (*r)++;
    }
    return node;
}

struct RBT_Node* RBT_min(struct RBT* tree, struct RBT_Node* node, long* r) {
    while (node->left != tree->nil) { // double read
        node = node->left; // read
        (*r) += 3;
    }
    (*r) += 2;
    return node;
}

void transplant(struct RBT* tree, struct RBT_Node* u, struct RBT_Node* v, long* r, long* w, bool calc_height) {
    if (u->parent == tree->nil) { // read
        tree->root = v; // write
    } else if (u == u->parent->left) { // double read
        u->parent->left = v; // read and write
        (*r) += 3;
    } else {
        u->parent->right = v; // read and write
        (*r) += 3;
    }
    
    v->parent = u->parent; // write

    if (calc_height) {
        if (v == tree->nil) { // read
            height_fixup(tree, v->parent, r); // read
            (*r)++;
        } else {
            height_fixup(tree, v, r);
        }
        (*r)++;
    }

    (*r)++;
    (*w) += 2;
}

void RBT_delete_fixup(struct RBT* tree, struct RBT_Node* node, long* r, long* w, bool calc_height) {
    struct RBT_Node* z;

    while (node != tree->root && !node->red) { // read
        if (node == node->parent->left) { // double read
            z = node->parent->right; // double read
            if (z->red) {
                z->red = false;
                node->parent->red = true; // read
                left_rotate(tree, node->parent, r, w, calc_height); // read
                z = node->parent->right; // double read
                (*r) += 4;
            }

            if (!z->left->red && !z->right->red) { // double read
                z->red = true;
                node = node->parent; // read
                (*r)++;
            } else {
                if (!z->right->red) { // read
                    z->left->red = false; // read
                    z->red = true;
                    right_rotate(tree, z, r, w, calc_height);
                    z = node->parent->right; // double read
                    (*r) += 3;
                }
                z->red = node->parent->red; // read
                node->parent->red = false; // read
                z->right->red = false; // read
                left_rotate(tree, node->parent, r, w, calc_height); // read
                node = tree->root; // read
                (*r) += 6;
            }
        } else {
            z = node->parent->left; // double read
            if (z->red) {
                z->red = false;
                node->parent->red = true; // read
                right_rotate(tree, node->parent, r, w, calc_height); // read
                z = node->parent->left; // double read
                (*r) += 4;
            }

            if (!z->left->red && !z->right->red) { // double read
                z->red = true;
                node = node->parent; // read
                (*r)++;
            } else {
                if (!z->left->red) { // read
                    z->right->red = false; // read
                    z->red = true;
                    left_rotate(tree, z, r, w, calc_height);
                    z = node->parent->left; // double read
                    (*r) += 3;
                }
                z->red = node->parent->red; // read
                node->parent->red = false; // read
                z->left->red = false; // read
                right_rotate(tree, node->parent, r, w, calc_height); // read
                node = tree->root; // read
                (*r) += 6;
            }
        }
        (*r) += 3;
    }
    (*r)++;
    node->red = false;
}

// deletes values from a tree
// returns -1 if the value isn't present
// or 0 if delete was successful
int RBT_delete(struct RBT* tree, long value, long* comps, long* r, long* w, bool calc_height) {
    struct RBT_Node* z = RBT_search(tree, tree->root, value, comps, r); // read
    if (z == tree->nil) 
        return -1;
    
    struct RBT_Node* x;
    struct RBT_Node* y = z;
    bool y_org_color = y->red;

    if (z->left == tree->nil) { // double read
        x = z->right; // read
        transplant(tree, z, x, r, w, calc_height);

        (*r)++;        
    } else if (z->right == tree->nil) { // double read
        x = z->left; // read
        transplant(tree, z, x, r, w, calc_height);

        (*r) += 3;
    } else {
        y = RBT_min(tree, z->right, r); // read
        y_org_color = y->red;

        x = y->right; // read

        if (y->parent == z) {
            x->parent = y;
        } else { // read
            transplant(tree, y, x, r, w, calc_height); 
            y->right = z->right; // read and write
            y->right->parent = y; // read and write
            (*r) += 2;
            (*w) += 2;
        }
        transplant(tree, z, y, r, w, calc_height);
        y->left = z->left; // read and write
        y->left->parent = y; // read and write
        y->red = z->red;

        (*r) += 7;
        (*w) += 2;
    }

    free(z);

    (*r) += 3;

    if (!y_org_color) {
        RBT_delete_fixup(tree, x, r, w, calc_height);
    }

    return 0;
}


// deletes values from a tree
unsigned int RBT_height(struct RBT_Node* root) {
    return root->height;
}

void RBT_print1(struct RBT* tree, struct RBT_Node* node, int depth, char prefix[4], char* lprefix, char* rprefix) {
    if (node == tree->nil)
        return;
    
    RBT_print1(tree, node->right, depth + 1, "⌈", lprefix, rprefix);
    
    if (prefix == NULL) {
        printf("%ld|%s\n", node->value, (node->red ? "r" : "b"));
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

        printf("%s%ld|%s\n", prefix, node->value, (node->red ? "r" : "b"));
    }

    lprefix[depth] = ' ';
    rprefix[depth] = '|';
    RBT_print1(tree, node->left, depth + 1, "⌊", lprefix, rprefix);

}

void RBT_print(struct RBT* tree) {
    if (tree == NULL) {
        return;
    }
    
    unsigned int h = RBT_height(tree->root);

    char* lprefix = malloc(sizeof(char) * h);
    char* rprefix = malloc(sizeof(char) * h);

    for (unsigned int i = 0; i < h; i++) {
        lprefix[i] = ' ';
        rprefix[i] = ' ';
    }
    
    RBT_print1(tree, tree->root, 0, NULL, lprefix, rprefix);

    free(lprefix);
    free(rprefix);
}
