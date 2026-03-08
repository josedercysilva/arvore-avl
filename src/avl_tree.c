/**
 * @file avl_tree.c
 * @brief Implementation of a self-balancing AVL Tree.
 * * This file contains the logic for node manipulation, tree balancing
 * via rotations, and standard BST operations (insert, remove, search).
 */

#include "../include/avl_tree.h"

/* ========================================================================= *
 * PRIVATE UTILITY FUNCTIONS                       *
 * ========================================================================= */

/**
 * @brief Returns the maximum of two integers.
 */
static int max_value(int a, int b) {
    return (a > b) ? a : b;
}

/**
 * @brief Finds the node with the minimum value in a given tree.
 * * This is used primarily during deletion to find the inorder successor
 * (the leftmost leaf of the right subtree).
 * * @param node The root of the subtree to search.
 * @return Pointer to the node with the smallest value.
 */
static Node* get_min_value_node(Node* node) {
    Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

/* ========================================================================= *
 * PUBLIC TREE OPERATIONS                          *
 * ========================================================================= */

/**
 * @brief Allocates and initializes a new AVL tree node.
 * * @param value The integer value to store in the node.
 * @return Pointer to the newly created node, or NULL if allocation fails.
 */
Node* create_node(int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node != NULL) {
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->height = 0;
    }
    return new_node;
}

/**
 * @brief Retrieves the height of a given node safely.
 * * @param node Pointer to the node.
 * @return The height of the node, or -1 if the node is NULL.
 */
int get_height(Node *node) {
    if (node == NULL) return -1;
    return node->height;
}

/**
 * @brief Calculates the balance factor of a node.
 * * Balance Factor = Height of Left Subtree - Height of Right Subtree.
 * An AVL tree node is balanced if the factor is -1, 0, or 1.
 * * @param node Pointer to the node to check.
 * @return The balance factor integer.
 */
int get_balance(Node *node) {
    if (node != NULL)
        return (get_height(node->left) - get_height(node->right));
    return 0;
}

/* ========================================================================= *
 * ROTATION ALGORITHMS                             *
 * ========================================================================= */

/**
 * @brief Performs a standard Left Rotation.
 * @param node The unbalanced root node.
 * @return The new root after rotation.
 */
static Node* rotate_left(Node *node) {
    Node *y = node->right;
    Node *f = y->left;

    y->left = node;
    node->right = f;

    node->height = max_value(get_height(node->left), get_height(node->right)) + 1;
    y->height = max_value(get_height(y->left), get_height(y->right)) + 1;

    return y;
}

/**
 * @brief Performs a standard Right Rotation.
 * @param node The unbalanced root node.
 * @return The new root after rotation.
 */
static Node* rotate_right(Node *node) {
    Node *y = node->left;
    Node *f = y->right;

    y->right = node;
    node->left = f;

    node->height = max_value(get_height(node->left), get_height(node->right)) + 1;
    y->height = max_value(get_height(y->left), get_height(y->right)) + 1;

    return y;
}

/**
 * @brief Performs a Right-Left Double Rotation.
 */
static Node* rotate_right_left(Node *node) {
    node->right = rotate_right(node->right);
    return rotate_left(node);
}

/**
 * @brief Performs a Left-Right Double Rotation.
 */
static Node* rotate_left_right(Node *node) {
    node->left = rotate_left(node->left);
    return rotate_right(node);
}

/**
 * @brief Evaluates the node's balance and applies necessary rotations.
 * * @param root The root node of the subtree to balance.
 * @return The new root of the balanced subtree.
 */
static Node* balance_node(Node *root) {
    int balance = get_balance(root);

    // Left Heavy Cases
    if (balance > 1 && get_balance(root->left) >= 0)
        return rotate_right(root);
    if (balance > 1 && get_balance(root->left) < 0)
        return rotate_left_right(root);

    // Right Heavy Cases
    if (balance < -1 && get_balance(root->right) <= 0)
        return rotate_left(root);
    if (balance < -1 && get_balance(root->right) > 0)
        return rotate_right_left(root);

    return root;
}

/* ========================================================================= *
 * CORE AVL OPERATIONS                             *
 * ========================================================================= */

/**
 * @brief Inserts a new value into the AVL tree.
 * * Recursively traverses the tree to find the correct insertion point,
 * updates heights, and rebalances the tree on the way back up.
 * * @param root Pointer to the tree's root.
 * @param value The value to be inserted.
 * @return The new root of the tree.
 */
Node* insert_node(Node *root, int value) {
    if (root == NULL) return create_node(value);

    if (value < root->value) {
        root->left = insert_node(root->left, value);
    } else if (value > root->value) {
        root->right = insert_node(root->right, value);
    } else {
        return root; // Duplicates are not allowed
    }

    root->height = max_value(get_height(root->left), get_height(root->right)) + 1;
    return balance_node(root);
}

/**
 * @brief Removes a specific value from the AVL tree.
 * * Handles cases for leaf nodes, single child nodes, and nodes with two children
 * (by replacing with the inorder successor). Rebalances the tree afterwards.
 * * @param root Pointer to the tree's root.
 * @param key The value to be removed.
 * @return The new root of the tree.
 */
Node* remove_node(Node *root, int key) {
    Node *temp;

    if (root == NULL) return root;

    if (key < root->value) {
        root->left = remove_node(root->left, key);
    } else if (key > root->value) {
        root->right = remove_node(root->right, key);
    } else {
        /* Node with one or no child */
        if (root->left == NULL) {
            temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            temp = root->left;
            free(root);
            return temp;
        }

        /* Node with two children: Get the inorder successor */
        temp = get_min_value_node(root->right);
        root->value = temp->value;
        root->right = remove_node(root->right, temp->value);
    }

    if (root == NULL) return root;

    root->height = max_value(get_height(root->left), get_height(root->right)) + 1;
    return balance_node(root);
}

/**
 * @brief Recursively prints the tree in a 2D format to the standard output.
 * * @param root Pointer to the tree's root.
 * @param level The current depth level (used for indentation).
 */
void print_tree(Node *root, int level) {
    int i;

    if (root != NULL) {
        print_tree(root->right, level + 1);
        printf("\n\n");

        for (i = 0; i < level; i++) {
            printf("\t");
        }

        printf("%d", root->value);
        print_tree(root->left, level + 1);
    }
}

/**
 * @brief Safely deallocates all memory used by the tree.
 * * Performs a post-order traversal to ensure children are freed
 * before their parent node.
 * * @param root Pointer to the tree's root.
 */
void free_tree(Node *root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}
