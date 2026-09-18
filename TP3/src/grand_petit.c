#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Programme : grand_petit.c
 * Description : Remplit un tableau de 100 entiers avec des valeurs aléatoires
 *               entre 1 et 1000 inclus, puis trouve et affiche le numéro
 *               le plus grand et le plus petit.
 */

#define TAILLE 100

int main(void) {
    int tableau[TAILLE];

    /* Initialisation du générateur de nombres aléatoires */
    srand((unsigned int)time(NULL));

    /* Remplissage du tableau avec des entiers entre 1 et 1000 */
    for (int i = 0; i < TAILLE; i++) {
        tableau[i] = rand() % 1000 + 1;
    }

    /* Initialisation du max et du min avec le premier élément */
    int plus_grand = tableau[0];
    int plus_petit = tableau[0];

    /* Parcours du tableau pour déterminer le plus grand et le plus petit */
    for (int i = 1; i < TAILLE; i++) {
        if (tableau[i] > plus_grand) {
            plus_grand = tableau[i];
        }
        if (tableau[i] < plus_petit) {
            plus_petit = tableau[i];
        }
    }

    /* Affichage des résultats */
    printf("Le numéro le plus grand est : %d\n", plus_grand);
    printf("Le numéro le plus petit est : %d\n", plus_petit);

    return 0;
}
