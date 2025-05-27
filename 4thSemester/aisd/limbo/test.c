#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct BST_Node {
    struct BST_Node* parent;
    long value;
    long height;
    struct BST_Node* left;
    struct BST_Node* right;
};

bool compare(int v1, int v2) {
    return v1 < v2;
}

bool compare_equal(int v1, int v2) {
    return v1 == v2;
}

struct BST_Node* BST_insert(struct BST_Node* node, long value) {
    if (node == NULL) {
        struct BST_Node* leaf = malloc(sizeof(struct BST_Node));

        leaf->left = NULL;
        leaf->right = NULL;
        leaf->parent = NULL;
        leaf->value = value;
        leaf->height = 1;

        return leaf;
    }
    

    if (compare(value, node->value)) {
        if (node->left == NULL) {
            struct BST_Node* leaf = malloc(sizeof(struct BST_Node));

            leaf->left = NULL;
            leaf->right = NULL;
            leaf->parent = node;
            leaf->value = value;
            leaf->height = 1;
            
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
            leaf->height = 1;
            
            node->right = leaf;

            return NULL;
        } else {
            return BST_insert(node->right, value);
        }
    }
}

struct BST_Node* ins2(struct BST_Node* node, long value) {
    if (node == NULL) {
        struct BST_Node* leaf = malloc(sizeof(struct BST_Node));

        leaf->left = NULL;
        leaf->right = NULL;
        leaf->parent = NULL;
        leaf->value = value;
        leaf->height = 1;

        return leaf;
    }

    while(node->left != NULL || node->right != NULL) {
        if (compare(node->value, value)) {
            if (node->left == NULL) {
                struct BST_Node* leaf = malloc(sizeof(struct BST_Node));

                leaf->left = NULL;
                leaf->right = NULL;
                leaf->parent = node;
                leaf->value = value;
                leaf->height = 1;
                
                node->left = leaf;

                return NULL;
            } else {
                node = node->left;
            }
        } else {
            if (node->right == NULL) {
                struct BST_Node* leaf = malloc(sizeof(struct BST_Node));

                leaf->left = NULL;
                leaf->right = NULL;
                leaf->parent = node;
                leaf->value = value;
                leaf->height = 1;
                
                node->right = leaf;

                return NULL;
            } else {
                node = node->right;
            }
        }
    }

    if (compare(node->value, value)) {
        struct BST_Node* leaf = malloc(sizeof(struct BST_Node));

        leaf->left = NULL;
        leaf->right = NULL;
        leaf->parent = node;
        leaf->value = value;
        leaf->height = 1;
        
        node->left = leaf;

        return NULL;
    } else {
        struct BST_Node* leaf = malloc(sizeof(struct BST_Node));

        leaf->left = NULL;
        leaf->right = NULL;
        leaf->parent = node;
        leaf->value = value;
        leaf->height = 1;
        
        node->right = leaf;

        return NULL;
    }
}

int main() {

    struct BST_Node *root = NULL;
    root = BST_insert(root, 0);
    for (int i = 1; i < 30000; i++) {
        BST_insert(root, i);
    }

    return 0;
}