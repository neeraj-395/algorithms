#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    double value;
    struct Node *left;
    struct Node *right;
} Node;

Node *init_node(double value) {
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void destroy_tree(Node *root) {
    if(root == NULL) return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

#endif // BINARY_TREE_H