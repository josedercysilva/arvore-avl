/**
 * @file avl_tree.h
 * @brief Public API and data structures for the AVL Tree implementation.
 * * This header defines the core Node structure and exposes the standard
 * functions required to create, manipulate, and free a self-balancing
 * AVL (Adelson-Velsky and Landis) binary search tree.
 */

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @struct Node
 * @brief Represents a single node within the AVL Tree.
 */
typedef struct Node {
    int value;                  /**< The integer value stored in the node */
    struct Node *left;          /**< Pointer to the left child node */
    struct Node *right;         /**< Pointer to the right child node */
    int height;                 /**< Height of the node for balance factor calculation */
} Node;

/**
 * @brief Allocates and initializes a new AVL tree node.
 * @param value The integer value to store in the node.
 * @return Pointer to the newly created node.
 */
Node* create_node(int value);

/**
 * @brief Retrieves the height of a given node safely.
 * @param node Pointer to the node.
 * @return The height of the node, or -1 if the node is NULL.
 */
int get_height(Node *node);

/**
 * @brief Calculates the balance factor of a node.
 * @param node Pointer to the node to check.
 * @return The balance factor integer (left height - right height).
 */
int get_balance(Node *node);

/**
 * @brief Inserts a new value into the AVL tree and rebalances it.
 * @param root Pointer to the tree's root.
 * @param value The value to be inserted.
 * @return The new root of the tree after insertion and balancing.
 */
Node* insert_node(Node *root, int value);

/**
 * @brief Removes a specific value from the AVL tree and rebalances it.
 * @param root Pointer to the tree's root.
 * @param key The value to be removed.
 * @return The new root of the tree after deletion and balancing.
 */
Node* remove_node(Node *root, int key);

/**
 * @brief Recursively prints the tree in a 2D format to the standard output.
 * @param root Pointer to the tree's root.
 * @param level The current depth level (used for indentation).
 */
void print_tree(Node *root, int level);

/**
 * @brief Safely deallocates all memory used by the tree.
 * @param root Pointer to the tree's root.
 */
void free_tree(Node *root);

#endif // AVL_TREE_H
