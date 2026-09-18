#include <stdio.h>

int main(void) {
    int compteur = 5;

    if (compteur <= 0 || compteur >= 10) {
        printf("La valeur de compteur doit être strictement positive et inférieure à 10.\n");
        return 1;
    }

    /* --- Version 1 : Boucles for imbriquées --- */
    printf("=== Version for (taille %d) ===\n", compteur);
    for (int i = 0; i < compteur; i++) {
        for (int j = 0; j <= i; j++) {
            /* Bordure gauche, hypoténuse ou base */
            if (j == 0 || j == i || i == compteur - 1) {
                printf("* ");
            } else {
                printf("# ");
            }
        }
        printf("\n");
    }

    printf("\n");

    /* --- Version 2 : Boucles while imbriquées avec break --- */
    printf("=== Version while (taille %d) ===\n", compteur);
    int i = 0;
    while (i < compteur) {
        int j = 0;
        while (1) {
            if (j > i) {
                break; /* Fin de la ligne */
            }

            if (j == 0 || j == i || i == compteur - 1) {
                printf("* ");
            } else {
                printf("# ");
            }

            j++;
        }
        printf("\n");
        i++;
    }

    return 0;
}