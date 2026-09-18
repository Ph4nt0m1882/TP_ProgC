#include <stdio.h>
#include "operator.h"

/**
 * Fichier source : operator.c
 * Description : Implémentation des fonctions arithmétiques et logiques
 *               avec utilisation d'une structure switch pour la sélection.
 */

int somme(int num1, int num2) {
    return num1 + num2;
}

int difference(int num1, int num2) {
    return num1 - num2;
}

int produit(int num1, int num2) {
    return num1 * num2;
}

int quotient(int num1, int num2) {
    if (num2 == 0) {
        printf("Erreur : Division par zéro !\n");
        return 0;
    }
    return num1 / num2;
}

int modulo(int num1, int num2) {
    if (num2 == 0) {
        printf("Erreur : Modulo par zéro !\n");
        return 0;
    }
    return num1 % num2;
}

int et(int num1, int num2) {
    return num1 & num2;
}

int ou(int num1, int num2) {
    return num1 | num2;
}

int negation(int num1, int num2) {
    (void)num2; /* num2 non utilisé pour la négation unaire */
    return ~num1;
}

int calculer(char op, int num1, int num2) {
    switch (op) {
        case '+':
            return somme(num1, num2);
        case '-':
            return difference(num1, num2);
        case '*':
            return produit(num1, num2);
        case '/':
            return quotient(num1, num2);
        case '%':
            return modulo(num1, num2);
        case '&':
            return et(num1, num2);
        case '|':
            return ou(num1, num2);
        case '~':
            return negation(num1, num2);
        default:
            printf("Opérateur non reconnu : %c\n", op);
            return 0;
    }
}
