#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definição da estrutura do nó
typedef struct Node {
    int value;
    struct Node *left, *right;
    int height;
} Node;

// Protótipos das funções públicas
Node* create_node(int value);
int get_height(Node *node);
int get_balance(Node *node);
Node* insert_node(Node *root, int value);
Node* remove_node(Node *root, int key);
void print_tree(Node *root, int level);
void free_tree(Node *root);

#endif // AVL_TREE_H
