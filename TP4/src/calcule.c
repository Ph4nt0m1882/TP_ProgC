#include <stdio.h>
#include <stdlib.h>
#include "operator.h"

/**
 * Programme : calcule.c
 * Description : Calculatrice en ligne de commande réalisant des opérations
 *               arithmétiques et logiques (+, -, *, /, %, &, |, ~).
 * Exemples :
 *   ./calcule + 10 5
 *   ./calcule '*' 7 8
 *   ./calcule | 5 3
 *   ./calcule ~ 5
 */

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage : %s <opérateur> <num1> [num2]\n", argv[0]);
        printf("Opérateurs supportés : +, -, '*', /, %%, &, |, ~\n");
        return 1;
    }

    char op = argv[1][0];
    int num1 = atoi(argv[2]);
    int num2 = (argc >= 4) ? atoi(argv[3]) : 0;

    int resultat = 0;
    switch (op) {
        case '+':
            resultat = somme(num1, num2);
            break;
        case '-':
            resultat = difference(num1, num2);
            break;
        case '*':
            resultat = produit(num1, num2);
            break;
        case '/':
            resultat = quotient(num1, num2);
            break;
        case '%':
            resultat = modulo(num1, num2);
            break;
        case '&':
            resultat = et(num1, num2);
            break;
        case '|':
            resultat = ou(num1, num2);
            break;
        case '~':
            resultat = negation(num1, num2);
            break;
        default:
            printf("Opérateur non supporté : %c\n", op);
            return 1;
    }

    printf("Résultat : %d\n", resultat);
    return 0;
}
