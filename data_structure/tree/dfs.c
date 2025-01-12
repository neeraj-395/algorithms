#include "binary_tree.h"

void insert_left(Node *parent, double value) {
    if(!parent->left) {
        parent->left = init_node(value);
    } else {
        Node *new_node = init_node(value);
        new_node->left = parent->left;
        parent->left = new_node;        
    }
}

void insert_right(Node *parent, double value) {
    if(!parent->right) {
        parent->right = init_node(value);
    } else {
        Node *new_node = init_node(value);
        new_node->right = parent->right;
        parent->right = new_node;        
    }
}

void pre_order(Node *root) {
    if(!root) return;
    printf("%f ", root->value);
    if(root->left) pre_order(root->left);
    if(root->right) pre_order(root->right);
}

void in_order(Node *root) {
    if(!root) return;
    if(root->left) pre_order(root->left);
    printf("%f ", root->value);
    if(root->right) pre_order(root->right);
}

void post_order(Node *root) {
    if(!root) return;
    if(root->left) pre_order(root->left);
    if(root->right) pre_order(root->right);
    printf("%f ", root->value);
}

int main() {

    Node *btree = init_node(1);
    insert_left(btree, 2);
    insert_left(btree, 3);
    insert_left(btree, 4);

    insert_right(btree, 5);
    insert_right(btree, 6);
    insert_right(btree, 7);

    pre_order(btree); printf("\n");
    post_order(btree); printf("\n");
    in_order(btree); printf("\n");

    destroy_tree(btree);
    return 0;
}

