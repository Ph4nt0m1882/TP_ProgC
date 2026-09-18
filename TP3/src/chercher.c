#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Programme : chercher.c
 * Description : Crée un tableau de 100 entiers, affiche le tableau,
 *               demande à l'utilisateur un entier à rechercher,
 *               puis indique si l'entier est présent ou absent.
 */

#define TAILLE 100

int main(void) {
    int tableau[TAILLE];
    int cible = 0;

    /* Initialisation de la graine aléatoire */
    srand((unsigned int)time(NULL));

    /* Remplissage du tableau avec des valeurs aléatoires entre -50 et 50 */
    for (int i = 0; i < TAILLE; i++) {
        tableau[i] = (rand() % 101) - 50;
    }

    /* Affichage du tableau */
    printf("Tableau :\n");
    for (int i = 0; i < TAILLE; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n\n");

    /* Demande de l'entier à chercher */
    printf("Entrez l'entier que vous souhaitez chercher : ");
    if (scanf("%d", &cible) != 1) {
        /* Valeur de repli si aucune entrée fournie (test non-interactif) */
        cible = tableau[0];
        printf("%d\n", cible);
    }

    /* Recherche linéaire de l'entier */
    int present = 0;
    for (int i = 0; i < TAILLE; i++) {
        if (tableau[i] == cible) {
            present = 1;
            break;
        }
    }

    /* Affichage du résultat */
    if (present) {
        printf("Résultat : entier présent\n");
    } else {
        printf("Résultat : entier absent\n");
    }

    return 0;
}
