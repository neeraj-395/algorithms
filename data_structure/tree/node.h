#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    double value;
    struct Node *left;
    struct Node *right;
} Node;

Node *create_node(double value) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->value = value;
    return node;
}

void print_tree(Node *root) {
    if(root == NULL) return;
    print_tree(root->left);
    print_tree(root->right);
    printf("%.2f ", root->value);
}

void destroy_tree(Node *root) {
    if(root == NULL) return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

#endif // NODE_H