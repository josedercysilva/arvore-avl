#include "../include/avl_tree.h"

// Funções auxiliares privadas
static int max_value(int a, int b) {
    return (a > b) ? a : b;
}

static Node* get_min_value_node(Node* node) {
    Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Implementação das funções públicas
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

int get_height(Node *node) {
    if (node == NULL) return -1;
    return node->height;
}

int get_balance(Node *node) {
    if (node != NULL)
        return (get_height(node->left) - get_height(node->right));
    return 0;
}

static Node* rotate_left(Node *node) {
    Node *y = node->right;
    Node *f = y->left;

    y->left = node;
    node->right = f;

    node->height = max_value(get_height(node->left), get_height(node->right)) + 1;
    y->height = max_value(get_height(y->left), get_height(y->right)) + 1;

    return y;
}

static Node* rotate_right(Node *node) {
    Node *y = node->left;
    Node *f = y->right;

    y->right = node;
    node->left = f;

    node->height = max_value(get_height(node->left), get_height(node->right)) + 1;
    y->height = max_value(get_height(y->left), get_height(y->right)) + 1;

    return y;
}

static Node* rotate_right_left(Node *node) {
    node->right = rotate_right(node->right);
    return rotate_left(node);
}

static Node* rotate_left_right(Node *node) {
    node->left = rotate_left(node->left);
    return rotate_right(node);
}

static Node* balance_node(Node *root) {
    int balance = get_balance(root);

    if (balance < -1 && get_balance(root->right) <= 0)
        return rotate_left(root);
    if (balance > 1 && get_balance(root->left) >= 0)
        return rotate_right(root);
    if (balance > 1 && get_balance(root->left) < 0)
        return rotate_left_right(root);
    if (balance < -1 && get_balance(root->right) > 0)
        return rotate_right_left(root);

    return root;
}

Node* insert_node(Node *root, int value) {
    if (root == NULL) return create_node(value);

    if (value < root->value) {
        root->left = insert_node(root->left, value);
    } else if (value > root->value) {
        root->right = insert_node(root->right, value);
    } else {
        return root;
    }

    root->height = max_value(get_height(root->left), get_height(root->right)) + 1;
    return balance_node(root);
}

Node* remove_node(Node *root, int key) {
    Node *temp;

    if (root == NULL) return root;

    if (key < root->value) {
        root->left = remove_node(root->left, key);
    } else if (key > root->value) {
        root->right = remove_node(root->right, key);
    } else {
        if (root->left == NULL) {
            temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            temp = root->left;
            free(root);
            return temp;
        }

        temp = get_min_value_node(root->right);
        root->value = temp->value;
        root->right = remove_node(root->right, temp->value);
    }

    if (root == NULL) return root;

    root->height = max_value(get_height(root->left), get_height(root->right)) + 1;
    return balance_node(root);
}

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

void free_tree(Node *root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}
