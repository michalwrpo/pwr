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

struct BST_Node* BST_insert(struct BST_Node* node, long value, long* comps, long* r, long* w, bool calc_height) {
    if (node == NULL) {
        struct BST_Node* leaf = malloc(sizeof(struct BST_Node));

        leaf->left = NULL;
        leaf->right = NULL;
        leaf->parent = NULL;
        *w += 3;
        leaf->value = value;
        leaf->height = 1;

        return leaf;
    }
    
    while(node->left != NULL || node->right != NULL) {
        if (compare(value, node->value, comps)) {
            (*r)++;
            if (node->left == NULL) {
                struct BST_Node* leaf = malloc(sizeof(struct BST_Node));

                leaf->left = NULL;
                leaf->right = NULL;
                leaf->parent = node;
                leaf->value = value;
                leaf->height = 1;
                
                node->left = leaf;
                (*w) += 4;

                if (calc_height)
                    height_fixup(leaf, r);

                return NULL;
            } else {
                node = node->left;
            }
        } else {
            (*r)++;
            if (node->right == NULL) {
                struct BST_Node* leaf = malloc(sizeof(struct BST_Node));

                leaf->left = NULL;
                leaf->right = NULL;
                leaf->parent = node;
                leaf->value = value;
                leaf->height = 1;
                
                node->right = leaf;
                (*w) += 4;

                if (calc_height)
                    height_fixup(leaf, r);
                
                return NULL;
            } else {
                node = node->right;
            }
        }
    }

    if (compare(value, node->value, comps)) {
        struct BST_Node* leaf = malloc(sizeof(struct BST_Node));

        leaf->left = NULL;
        leaf->right = NULL;
        leaf->parent = node;
        leaf->value = value;
        leaf->height = 1;
        
        node->left = leaf;
        (*w) += 4;

        if (calc_height)
            height_fixup(leaf, r);

        return NULL;
    } else {
        struct BST_Node* leaf = malloc(sizeof(struct BST_Node));

        leaf->left = NULL;
        leaf->right = NULL;
        leaf->parent = node;
        leaf->value = value;
        leaf->height = 1;
        
        node->right = leaf;
        (*w) += 4;

        if (calc_height)
            height_fixup(leaf, r);
        
        return NULL;
    }
}

// deletes values from a tree
// returns -1 if the value isn't present
// 0 if delete was successful
// and 1 if the entire tree was deleted
int BST_delete(struct BST_Node* node, long value, long* comps, long* r, long* w, bool calc_height) {
    while(node != NULL) {
        if (compare(value, node->value, comps)) {
            node = node->left;
        } else if (compare(node->value, value, comps)) {
            node = node->right;
        } else {
            break;
        }
    }

    if (node == NULL) 
        return -1;

    // no children
    (*r) += 2;
    if (node->left == NULL && node->right == NULL) {
        (*r)++;
        if (node->parent != NULL) {
            (*r)++;
            if (node->parent->left != NULL) {
                if (compare_equal(node->parent->left->value, value, comps)) {
                    node->parent->left = NULL;
                } else {
                    node->parent->right = NULL;
                }
            } else {
                node->parent->right = NULL;
            }
            (*w)++;

            if (calc_height)
                height_fixup(node, r);

            free(node);
            return 0;
        }

        free(node);
        return 1;
    }
    
    // only right child
    (*r)++;
    if (node->left == NULL) {
        struct BST_Node* temp = node->right;

        node->value = node->right->value;
        node->height = node->right->height;

        (*r) += 2;
        if (node->right->right != NULL) 
            node->right->right->parent = node;
        if (node->right->left != NULL)
            node->right->left->parent = node;
            
        node->left = node->right->left;
        node->right = node->right->right;
        (*w) += 3;

        if (calc_height)
            height_fixup(temp, r);

        free(temp);
        return 0;
    }
    
    // only left child
    (*r)++;
    if (node->right == NULL) {
        struct BST_Node* temp = node->left;

        node->value = node->left->value;
        node->height = node->left->height;

        (*r) += 2;
        if (node->left->right != NULL) 
            node->left->right->parent = node;
        if (node->left->left != NULL)
            node->left->left->parent = node;

        node->right = node->left->right;
        node->left = node->left->left;
        (*w) += 3;

        if (calc_height)
            height_fixup(temp, r);

        free(temp);
        return 0;
    }

    // both children
    // next is the successor of node in the subtree with node as root 
    struct BST_Node* next = node->right;
    
    (*r)++;
    while (next->left != NULL) {
        next = next->left;
    }

    int new_value = next->value;
    // delete next in O(1), due to how it was found, it has at most one child
    BST_delete(next, new_value, comps, r, w, calc_height); 

    node->value = new_value;
    return 0;
}

unsigned int BST_height(struct BST_Node* node) {
    if (node == NULL)
        return 0;
    
    // return 1 + max(BST_height(node->left), BST_height(node->right));
    return node->height;
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

void BST_print(struct BST_Node* node) {
    unsigned int h = BST_height(node);

    char* lprefix = malloc(sizeof(char) * h);
    char* rprefix = malloc(sizeof(char) * h);

    for (unsigned int i = 0; i < h; i++) {
        lprefix[i] = ' ';
        rprefix[i] = ' ';
    }
    
    BST_print1(node, 0, NULL, lprefix, rprefix);

    free(lprefix);
    free(rprefix);
}
