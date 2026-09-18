#include <stdio.h>
#include "fichier.h"

/**
 * Fichier source : fichier.c
 * Description : Fonctions pour lire le contenu d'un fichier et écrire un message
 *               dans un fichier.
 */

int lire_fichier(const char *nom_de_fichier) {
    FILE *f = fopen(nom_de_fichier, "r");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier \"%s\" en lecture.\n", nom_de_fichier);
        return -1;
    }

    printf("Contenu du fichier %s :\n", nom_de_fichier);
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        printf("%s", buffer);
    }
    printf("\n");

    fclose(f);
    return 0;
}

int ecrire_dans_fichier(const char *nom_de_fichier, const char *message) {
    FILE *f = fopen(nom_de_fichier, "a");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier \"%s\" en écriture.\n", nom_de_fichier);
        return -1;
    }

    fprintf(f, "%s\n", message);
    fclose(f);
    printf("Le message a été écrit dans le fichier %s.\n", nom_de_fichier);
    return 0;
}
