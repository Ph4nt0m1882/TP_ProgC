#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Programme : tri.c
 * Description : Remplit un tableau de 100 entiers, affiche le tableau non trié,
 *               le trie par ordre croissant (tri à bulles), puis affiche le tableau trié.
 */

#define TAILLE 100

int main(void) {
    int tableau[TAILLE];

    /* Initialisation de la graine aléatoire */
    srand((unsigned int)time(NULL));

    /* Remplissage avec des valeurs aléatoires entre -50 et 50 */
    for (int i = 0; i < TAILLE; i++) {
        tableau[i] = (rand() % 101) - 50;
    }

    /* Affichage du tableau non trié */
    printf("Tableau non trié :\n");
    for (int i = 0; i < TAILLE; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n\n");

    /* Tri à bulles par ordre croissant */
    for (int i = 0; i < TAILLE - 1; i++) {
        for (int j = 0; j < TAILLE - 1 - i; j++) {
            if (tableau[j] > tableau[j + 1]) {
                int temp = tableau[j];
                tableau[j] = tableau[j + 1];
                tableau[j + 1] = temp;
            }
        }
    }

    /* Affichage du tableau trié */
    printf("Tableau trié par ordre croissant :\n");
    for (int i = 0; i < TAILLE; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n");

    return 0;
}
