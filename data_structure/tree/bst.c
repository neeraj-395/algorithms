/* BINARY SEARCH TREE */

#include "node.h"

Node *insert_node(Node *root, double value) {
    if(root == NULL) return create_node(value);
    if(root->value > value) {
        root->left = insert_node(root->left, value);
    } else if(root->value < value) {
        root->right = insert_node(root->right, value);
    } return root;
}

Node *search_node(Node *root, double value) {
    if(root == NULL || root->value == value) return root;
    if(value < root->value) {
        return search_node(root->left, value);
    } return search_node(root->right, value);
}


int main(void) {
    Node *bst = create_node(5);
    bst = insert_node(bst, 15);
    bst = insert_node(bst, 11);
    bst = insert_node(bst, 10);
    bst = insert_node(bst, 18);

    printf("Search Result: %.2f\n", search_node(bst, 5)->value);

    destroy_tree(bst);

    return 0;
}
