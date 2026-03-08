/**
 * @file main.c
 * @brief Command-line interface for the AVL Tree application.
 * * This file contains the main execution loop, handling user input safely,
 * and dispatching the appropriate AVL tree operations.
 */

#include <stdio.h>
#include "../include/avl_tree.h"

/**
 * @brief Displays the interactive menu options to the user.
 */
void print_menu() {
    printf("\n\n\t0 - Sair\n\t1 - Inserir\n\t2 - Remover\n\t3 - Imprimir\n\n");
    printf("Escolha uma opcao: ");
}

/**
 * @brief Safely reads an integer from the standard input.
 * * Prevents infinite loops and buffer corruption if the user enters
 * non-numeric characters (like letters or symbols) by clearing the input buffer.
 * * @return The integer entered by the user, or -1 if the input was invalid.
 */
int get_safe_input() {
    int input;
    if (scanf("%d", &input) != 1) {
        while(getchar() != '\n'); // Clear the input buffer
        return -1;
    }
    return input;
}

/**
 * @brief Main execution function.
 * * Initializes the tree, manages the user interaction loop, and ensures
 * all memory is safely freed before the program terminates.
 * * @return 0 upon successful execution.
 */
int main() {
    int option, value;
    Node *root = NULL;

    do {
        print_menu();
        option = get_safe_input();

        switch(option) {
            case 0:
                printf("\tLimpando memoria e saindo...\n");
                free_tree(root);
                break;
            case 1:
                printf("\tDigite o valor a ser inserido: ");
                value = get_safe_input();
                if (value != -1) root = insert_node(root, value);
                break;
            case 2:
                printf("\tDigite o valor a ser removido: ");
                value = get_safe_input();
                if (value != -1) root = remove_node(root, value);
                break;
            case 3:
                print_tree(root, 1);
                break;
            case -1:
                printf("\n\tEntrada invalida! Digite apenas numeros.\n");
                break;
            default:
                printf("\n\tOpcao invalida!\n");
        }
    } while(option != 0);

    return 0;
}
