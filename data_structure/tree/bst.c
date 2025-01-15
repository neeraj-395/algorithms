/* BINARY SEARCH TREE */

#include "node.h"

void insert_node(Node *root, double value) {
    if(root->value >= value && root->left) {
        return insert_node(root->left, value);
    } else if(root->value <= value && root->right) {
        return insert_node(root->right, value);
    } else root->value = value;
}

void delete_node(Node *root) {

}

Node *search_node(Node *root, double value) {
    if(root->value == value) {
        
    }  
}
