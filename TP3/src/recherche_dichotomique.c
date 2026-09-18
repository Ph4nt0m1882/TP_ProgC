#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Programme : recherche_dichotomique.c
 * Description : Crée un tableau de 100 entiers triés par ordre croissant,
 *               affiche le tableau, demande à l'utilisateur un entier,
 *               puis effectue une recherche dichotomique pour vérifier
 *               sa présence.
 */

#define TAILLE 100

int main(void) {
    int tableau[TAILLE];
    int cible = 0;

    /* Initialisation de la graine aléatoire */
    srand((unsigned int)time(NULL));

    /* Remplissage avec des entiers croissants */
    int valeur = (rand() % 10) - 20;
    for (int i = 0; i < TAILLE; i++) {
        valeur += (rand() % 5) + 1; /* Incrément de 1 à 5 pour garantir le tri */
        tableau[i] = valeur;
    }

    /* Affichage du tableau trié */
    printf("Tableau trié :\n");
    for (int i = 0; i < TAILLE; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n\n");

    /* Demande de l'entier à chercher */
    printf("Entrez l'entier que vous souhaitez chercher : ");
    if (scanf("%d", &cible) != 1) {
        /* Valeur par défaut si exécution non interactive */
        cible = tableau[TAILLE / 2];
        printf("%d\n", cible);
    }

    /* Recherche dichotomique */
    int debut = 0;
    int fin = TAILLE - 1;
    int present = 0;

    while (debut <= fin) {
        int milieu = debut + (fin - debut) / 2;
        if (tableau[milieu] == cible) {
            present = 1;
            break;
        } else if (tableau[milieu] < cible) {
            debut = milieu + 1;
        } else {
            fin = milieu - 1;
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
