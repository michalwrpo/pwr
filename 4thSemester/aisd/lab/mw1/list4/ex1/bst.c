#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

int max(int num1, int num2) {
    return num1 > num2 ? num1 : num2;
}

struct BST_Node* BST_insert(struct BST_Node* node, long value) {
    if (node == NULL) {
        struct BST_Node* leaf = malloc(sizeof(struct BST_Node));

        leaf->left = NULL;
        leaf->right = NULL;
        leaf->parent = NULL;
        leaf->value = value;

        return leaf;
    }
    

    if (value < node->value) {
        if (node->left == NULL) {
            struct BST_Node* leaf = malloc(sizeof(struct BST_Node));

            leaf->left = NULL;
            leaf->right = NULL;
            leaf->parent = node;
            leaf->value = value;

            node->left = leaf;
            
            return NULL;
        } else {
            return BST_insert(node->left, value);
        }
    } else {
        if (node->right == NULL) {
            struct BST_Node* leaf = malloc(sizeof(struct BST_Node));

            leaf->left = NULL;
            leaf->right = NULL;
            leaf->parent = node;
            leaf->value = value;

            node->right = leaf;
            
            return NULL;
        } else {
            return BST_insert(node->right, value);
        }
    }
}

int BST_delete(struct BST_Node* node, long value) {
    if (node == NULL) 
        return -1;
    
    if (value == node->value) {
        // no children
        if (node->left == NULL && node->right == NULL) {
            if (node->parent != NULL) {
                if (node->parent->left->value == value) {
                    node->parent->left = NULL;
                } else {
                    node->parent->right = NULL;
                }
            }
            free(node);
            return 0;
        }
        
        // only right child
        if (node->left == NULL) {
            if (node->parent != NULL) {
                if (node->parent->left->value == value) {
                    node->parent->left = node->right;
                } else {
                    node->parent->right = node->right;
                }
            }
            node->right->parent = node->parent;
            free(node);
            return 0;
        }
        
        // only left child
        if (node->right == NULL) {
            if (node->parent != NULL) {
                if (node->parent->left->value == value) {
                    node->parent->left = node->left;
                } else {
                    node->parent->right = node->left;
                }
            }
            node->left->parent = node->parent;
            free(node);
            return 0;
        }

        // both children
        // next is the successor of node in the subtree with node as root 
        struct BST_Node* next = node->right;
        
        while (next->left != NULL) {
            next = next->left;
        }

        int new_value = next->value;
        // delete next in O(1), due to how it was found, it has only one child
        BST_delete(next, new_value); 

        node->value = new_value;
        return 0;
    }
    
    if (value < node->value) {
        return BST_delete(node->left, value);
    }
    return BST_delete(node->right, value);
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

void BST_print(struct BST_Node* node) {
    int h = BST_height(node);

    char* lprefix = malloc(sizeof(char) * h);
    char* rprefix = malloc(sizeof(char) * h);

    for (int i = 0; i < h; i++) {
        lprefix[i] = ' ';
        rprefix[i] = ' ';
    }
    
    BST_print1(node, 0, NULL, lprefix, rprefix);

    free(lprefix);
    free(rprefix);
}

// int main() {
//     struct BST_Node *bst = BST_insert(NULL, 10);
//     BST_insert(bst, 8);
//     BST_insert(bst, 3);
//     BST_insert(bst, 5);
//     BST_insert(bst, 9);
//     BST_insert(bst, 14);
//     BST_insert(bst, 17);
//     BST_insert(bst, 12);
//     BST_insert(bst, 20);
//     BST_insert(bst, 1);
//     BST_insert(bst, 15);

//     BST_print(bst);

//     BST_delete(bst, 14);
//     BST_print(bst);

//     return 0;
// }