#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Programme : couleur_compteur.c
 * Description : Stocke 100 couleurs RGBA dans un tableau et compte le nombre
 *               d'occurrences de chaque couleur distincte, puis affiche le résultat.
 */

#define NB_COULEURS 100

/* Structure représentant une couleur RGBA */
struct Couleur {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

/* Structure associant une couleur distincte et son nombre d'occurrences */
struct CouleurCompteur {
    struct Couleur couleur;
    int occurrences;
};

/* Fonction utilitaire pour comparer deux couleurs */
static int couleurs_identiques(struct Couleur c1, struct Couleur c2) {
    return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a);
}

int main(void) {
    struct Couleur tableau[NB_COULEURS];
    struct CouleurCompteur distinctes[NB_COULEURS];
    int nb_distinctes = 0;

    /* Palette de base pour générer des répétitions significatives parmi les 100 éléments */
    struct Couleur palette[5] = {
        {0xff, 0x23, 0x23, 0x45},
        {0xff, 0x00, 0x23, 0x12},
        {0x00, 0xff, 0x00, 0xff},
        {0x00, 0x00, 0xff, 0xff},
        {0x12, 0x34, 0x56, 0x78}
    };

    /* Initialisation de la graine aléatoire */
    srand((unsigned int)time(NULL));

    /* Remplissage des 100 couleurs à partir de la palette */
    for (int i = 0; i < NB_COULEURS; i++) {
        tableau[i] = palette[rand() % 5];
    }

    /* Comptage des couleurs distinctes */
    for (int i = 0; i < NB_COULEURS; i++) {
        int trouve = 0;
        for (int j = 0; j < nb_distinctes; j++) {
            if (couleurs_identiques(tableau[i], distinctes[j].couleur)) {
                distinctes[j].occurrences++;
                trouve = 1;
                break;
            }
        }
        if (!trouve) {
            distinctes[nb_distinctes].couleur = tableau[i];
            distinctes[nb_distinctes].occurrences = 1;
            nb_distinctes++;
        }
    }

    /* Affichage des couleurs distinctes et de leur nombre d'occurrences */
    printf("Couleurs distinctes et occurrences (sur %d couleurs) :\n", NB_COULEURS);
    for (int i = 0; i < nb_distinctes; i++) {
        printf("0x%02x 0x%02x 0x%02x 0x%02x : %d\n",
               distinctes[i].couleur.r,
               distinctes[i].couleur.g,
               distinctes[i].couleur.b,
               distinctes[i].couleur.a,
               distinctes[i].occurrences);
    }

    return 0;
}
