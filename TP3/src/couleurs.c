#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Programme : couleurs.c
 * Description : Déclaration et manipulation d'un tableau de 100 couleurs RGBA.
 */

#define NB_COULEURS 100

/* Structure représentant une couleur RGBA */
struct Couleur {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

int main(void) {
    struct Couleur couleurs[NB_COULEURS];

    /* Initialisation du générateur aléatoire */
    srand((unsigned int)time(NULL));

    /* Remplissage de 100 couleurs */
    for (int i = 0; i < NB_COULEURS; i++) {
        couleurs[i].r = (unsigned char)(rand() % 256);
        couleurs[i].g = (unsigned char)(rand() % 256);
        couleurs[i].b = (unsigned char)(rand() % 256);
        couleurs[i].a = (unsigned char)(rand() % 256);
    }

    /* Affichage des couleurs */
    printf("Affichage des %d couleurs RGBA :\n", NB_COULEURS);
    for (int i = 0; i < NB_COULEURS; i++) {
        printf("Couleur %3d : 0x%02x 0x%02x 0x%02x 0x%02x\n",
               i + 1,
               couleurs[i].r,
               couleurs[i].g,
               couleurs[i].b,
               couleurs[i].a);
    }

    return 0;
}
