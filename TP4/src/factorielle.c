#include <stdio.h>

/**
 * Programme : factorielle.c
 * Description : Calcul de la factorielle d'un entier naturel de manière récursive.
 */

/* Définition de la fonction récursive factorielle */
int factorielle(int num) {
    if (num <= 0) {
        printf("fact(0): 1\n");
        return 1;
    } else {
        int valeur = num * factorielle(num - 1);
        printf("fact(%d): %d\n", num, valeur);
        return valeur;
    }
}

int main(void) {
    int valeurs_test[] = {0, 3, 5};
    int nb_tests = sizeof(valeurs_test) / sizeof(valeurs_test[0]);

    for (int i = 0; i < nb_tests; i++) {
        int n = valeurs_test[i];
        printf("Calcul de %d! :\n", n);
        int res = factorielle(n);
        printf("Résultat final de %d! = %d\n\n", n, res);
    }

    return 0;
}
