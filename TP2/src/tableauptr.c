#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Programme : tableauptr.c
 * Description : Remplit un tableau d'entiers et un tableau de flottants avec des
 *               valeurs aléatoires. Multiplie par 3 chaque valeur dont l'indice
 *               est divisible par 2 (indice pair).
 *               Parcours et modifications effectués exclusivement avec des pointeurs
 *               (sans notation indicielle []).
 */

#define TAILLE 10

int main(void) {
    int tab_int[TAILLE];
    float tab_float[TAILLE];

    /* Initialisation de la graine pour les nombres aléatoires */
    srand((unsigned int)time(NULL));

    /* Remplissage du tableau d'entiers avec des pointeurs */
    int *p_int = tab_int;
    for (int i = 0; i < TAILLE; i++, p_int++) {
        *p_int = rand() % 100 + 1; /* Entiers entre 1 et 100 */
    }

    /* Remplissage du tableau de flottants avec des pointeurs */
    float *p_float = tab_float;
    for (int i = 0; i < TAILLE; i++, p_float++) {
        *p_float = (float)(rand() % 1000) / 100.0f; /* Flottants avec 2 décimales */
    }

    /* Affichage avant multiplication : entiers */
    printf("Tableau d'entiers (avant la multiplication par 3) :\n");
    p_int = tab_int;
    for (int i = 0; i < TAILLE; i++, p_int++) {
        if (i > 0) printf(", ");
        printf("%d", *p_int);
    }
    printf("\n\n");

    /* Affichage avant multiplication : flottants */
    printf("Tableau de nombres à virgule flottante (avant la multiplication par 3) :\n");
    p_float = tab_float;
    for (int i = 0; i < TAILLE; i++, p_float++) {
        if (i > 0) printf(", ");
        printf("%.2f", *p_float);
    }
    printf("\n\n");

    /* Multiplication par 3 pour chaque position dont l'indice est divisible par 2 */
    p_int = tab_int;
    for (int i = 0; i < TAILLE; i++, p_int++) {
        if (i % 2 == 0) {
            *p_int *= 3;
        }
    }

    p_float = tab_float;
    for (int i = 0; i < TAILLE; i++, p_float++) {
        if (i % 2 == 0) {
            *p_float *= 3.0f;
        }
    }

    /* Affichage après multiplication : entiers */
    printf("Tableau d'entiers (après la multiplication par 3) :\n");
    p_int = tab_int;
    for (int i = 0; i < TAILLE; i++, p_int++) {
        if (i > 0) printf(", ");
        printf("%d", *p_int);
    }
    printf("\n\n");

    /* Affichage après multiplication : flottants */
    printf("Tableau de nombres à virgule flottante (après la multiplication par 3) :\n");
    p_float = tab_float;
    for (int i = 0; i < TAILLE; i++, p_float++) {
        if (i > 0) printf(", ");
        printf("%.2f", *p_float);
    }
    printf("\n");

    return 0;
}
