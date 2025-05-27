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

// fixes height of the given node and every above it
void height_fixup(struct RBT_Node* node, long* r) {
    while (node != NULL) {
        (*r) += 2;        
        if (node->left == NULL && node->right == NULL) {
            node->height = 1;
        } else if (node->left == NULL) {
            (*r)++;
            node->height = 1 + node->right->height;
        } else if (node->right == NULL) {
            (*r) += 2;        
            node->height = 1 + node->left->height;
        } else {
            (*r) += 2;        
            node->height = 1 + max(node->left->height, node->right->height);
        }
        node = node->parent;
    }
}

void left_rotate(struct RBT_Node* node, long* r, long* w, bool calc_height) {
    if (node == NULL) {
        return;
    }
    struct RBT_Node* y = node->right;
    (*r)++;
    if (y == NULL) {
        return;
    }
    node->right = y->left;
    (*r)++;
    if (y->left != NULL) {
        (*w)++;
        y->left->parent = node;
    }
    y->parent = node->parent;
    (*r)++;
    if (node->parent != NULL) {
        (*r)++;
        if (node == node->parent->left) {
            node->parent->left = y;
        } else {
            node->parent->right = y;
        }
    }

    y->left = node;
    node->parent = y;
    (*w) += 5;

    if (calc_height) {
        height_fixup(node, r);
    }
}

void right_rotate(struct RBT_Node* node, long* r, long* w, bool calc_height) {
    if (node == NULL) {
        return;
    }
    struct RBT_Node* y = node->left;
    (*r)++;
    if (y == NULL) {
        return;
    }
    node->left = y->right;
    (*r)++;
    if (y->right != NULL) {
        (*w)++;
        y->right->parent = node;
    }
    y->parent = node->parent;
    (*r)++;
    if (node->parent != NULL) {
        (*r)++;
        if (node == node->parent->left) {
            node->parent->left = y;
        } else {
            node->parent->right = y;
        }
    }

    y->right = node;
    node->parent = y;
    (*w) += 5;

    if (calc_height) {
        height_fixup(node, r);
    }
}

void RBT_insert_fixup(struct RBT_Node* node, long* r, long* w, bool calc_height) {
    if (node == NULL) {
        return;
    }
    
    (*r)++;
    if (node->parent == NULL) {
        return;
    }

    struct RBT_Node* y;
    (*r)++;
    while (node->parent->red) {
        (*r) += 2;
        if (node->parent->parent == NULL) {
            break;
        }
        (*r) += 2;
        if (node->parent == node->parent->parent->left) {
            y = node->parent->parent->right;
            (*r)++;
            if (y == NULL) {
                (*r)++;
                if (node == node->parent->right) {
                    node = node->parent;
                    left_rotate(node, r, w, calc_height);
                } else {
                    node->parent->red = false;
                    node->parent->parent->red = true;
                    (*r)++;
                    if (node->parent->parent->parent != NULL) {
                        right_rotate(node->parent->parent, r, w, calc_height);
                    } else {
                        break;
                    }   
                }
                continue;
            }
            
            (*r)++;
            if (y->red) {
                node->parent->red = false;
                y->red = false;
                node->parent->parent->red = true;
                
                (*r)++;
                if (node->parent->parent->parent != NULL) {
                    node = node->parent->parent;
                } else {
                    break;
                }
            } else if (node == node->parent->right) {
                (*r)++;
                node = node->parent;
                left_rotate(node, r, w, calc_height);
            } else {
                (*r)++;
                node->parent->red = false;
                node->parent->parent->red = true;
                (*r)++;
                if (node->parent->parent->parent != NULL) {
                    right_rotate(node->parent->parent, r, w, calc_height);
                } else {
                    break;
                }   
            }
        } else {
            y = node->parent->parent->left;
            (*r)++;
            if (y == NULL) {
                (*r)++;
                if (node == node->parent->left) {
                    node = node->parent;
                    right_rotate(node, r, w, calc_height);
                } else {
                    node->parent->red = false;
                    node->parent->parent->red = true;
                    (*r)++;
                    left_rotate(node->parent->parent, r, w, calc_height);
                }
                continue;
            }
            
            (*r)++;
            if (y->red) {
                node->parent->red = false;
                y->red = false;
                node->parent->parent->red = true;
                
                (*r)++;
                if (node->parent->parent->parent != NULL) {
                    node = node->parent->parent;
                } else {
                    break;
                }
            } else if (node == node->parent->left) {
                (*r)++;
                node = node->parent;
                right_rotate(node, r, w, calc_height);
            } else {
                (*r)++;
                node->parent->red = false;
                node->parent->parent->red = true;
                (*r)++;
                left_rotate(node->parent->parent, r, w, calc_height);
            }
        }
    }

    if (node == NULL) {
        return;
    }
        
    (*r)++;
    while (node->parent != NULL) {
        node = node->parent;
    }
    node->red = false;
}

struct RBT_Node* RBT_insert(struct RBT_Node* node, long value, long* comps, long* r, long* w, bool calc_height) {
    struct RBT_Node* root = node;
    struct RBT_Node* leaf = malloc(sizeof(struct RBT_Node));
    
    leaf->left = NULL;
    leaf->right = NULL;
    leaf->red = true;
    *w += 2;
    leaf->value = value;
    leaf->height = 1;
    
    if (node == NULL) {
        leaf->parent = NULL;
        leaf->red = false;
        (*w)++;
        return leaf;
    }

    struct RBT_Node* y = node->parent;
    
    while(node != NULL) {
        y = node;
        if (compare(value, node->value, comps)) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    (*w)++;
    leaf->parent = y;

    (*r)++;
    if (y != NULL) {
        (*w)++;
        if (compare(value, y->value, comps)) {
            y->left = leaf;
        } else {
            y->right = leaf;
        }
    }

    if (calc_height) {
        height_fixup(leaf, r);
    }

    RBT_insert_fixup(leaf, r, w, calc_height);
    
    (*r)++;
    while (root->parent != NULL) {
        (*r)++;
        root = root->parent;
    }

    return root;
}

// deletes values from a tree
// returns -1 if the value isn't present
// 0 if delete was successful
// and 1 if the entire tree was deleted
int RBT_delete(struct RBT_Node* node, long value, long* comps, long* r, long* w, bool calc_height) {
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
        struct RBT_Node* temp = node->right;

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
        struct RBT_Node* temp = node->left;

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
    struct RBT_Node* next = node->right;
    
    (*r)++;
    while (next->left != NULL) {
        next = next->left;
    }

    int new_value = next->value;
    // delete next in O(1), due to how it was found, it has at most one child
    RBT_delete(next, new_value, comps, r, w, calc_height); 

    node->value = new_value;
    return 0;
}

unsigned int RBT_height(struct RBT_Node* node) {
    if (node == NULL)
        return 0;
    
    // return 1 + max(BST_height(node->left), BST_height(node->right));
    return node->height;
}

void BST_print1(struct RBT_Node* node, int depth, char prefix[4], char* lprefix, char* rprefix) {
    if (node == NULL)
        return;
    
    BST_print1(node->right, depth + 1, "⌈", lprefix, rprefix);
    
    if (prefix == NULL) {
        printf("%ld|%s\n", node->value, node->red ? "r" : "b");
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

        printf("%s%ld|%s\n", prefix, node->value, node->red ? "r" : "b");
    }

    lprefix[depth] = ' ';
    rprefix[depth] = '|';
    BST_print1(node->left, depth + 1, "⌊", lprefix, rprefix);

}

void RBT_print(struct RBT_Node* node) {
    unsigned int h = RBT_height(node);

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
