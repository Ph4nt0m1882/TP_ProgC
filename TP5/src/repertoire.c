#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "repertoire.h"

/**
 * Programme : repertoire.c
 * Description : Implémentation des fonctions de parcours de répertoires :
 *               1. lire_dossier (Ex 5.1)
 *               2. lire_dossier_recursif (Ex 5.2)
 *               3. lire_dossier_iteratif (Ex 5.3)
 */

/* Exercice 5.1 : Parcours simple d'un répertoire */
void lire_dossier(const char *nom_repertoire) {
    DIR *d = opendir(nom_repertoire);
    if (d == NULL) {
        perror("Erreur opendir");
        return;
    }

    struct dirent *entree;
    printf("Contenu du répertoire \"%s\" :\n", nom_repertoire);
    while ((entree = readdir(d)) != NULL) {
        printf("%s\n", entree->d_name);
    }

    closedir(d);
}

/* Exercice 5.2 : Parcours récursif d'un répertoire et de ses sous-répertoires */
void lire_dossier_recursif(const char *nom_repertoire) {
    DIR *d = opendir(nom_repertoire);
    if (d == NULL) {
        perror("Erreur opendir");
        return;
    }

    struct dirent *entree;
    char chemin[2048];

    while ((entree = readdir(d)) != NULL) {
        /* Ignorer . et .. pour éviter les boucles infinies */
        if (strcmp(entree->d_name, ".") == 0 || strcmp(entree->d_name, "..") == 0) {
            continue;
        }

        snprintf(chemin, sizeof(chemin), "%s/%s", nom_repertoire, entree->d_name);
        printf("%s\n", chemin);

        /* Vérifier si l'entrée est un sous-répertoire */
        struct stat st;
        if (stat(chemin, &st) == 0 && S_ISDIR(st.st_mode)) {
            lire_dossier_recursif(chemin);
        }
    }

    closedir(d);
}

/* Exercice 5.3 : Parcours itératif d'un répertoire et de ses sous-répertoires */
#define MAX_QUEUE 512
#define PATH_LEN 1024

void lire_dossier_iteratif(const char *nom_repertoire) {
    char file_dossiers[MAX_QUEUE][PATH_LEN];
    int debut = 0;
    int fin = 0;

    /* Enfiler le dossier racine */
    strncpy(file_dossiers[fin++], nom_repertoire, PATH_LEN - 1);
    file_dossiers[fin - 1][PATH_LEN - 1] = '\0';

    printf("Parcours itératif à partir de \"%s\" :\n", nom_repertoire);

    while (debut < fin) {
        char courant[PATH_LEN];
        strncpy(courant, file_dossiers[debut++], PATH_LEN - 1);
        courant[PATH_LEN - 1] = '\0';

        DIR *d = opendir(courant);
        if (d == NULL) {
            continue;
        }

        struct dirent *entree;
        while ((entree = readdir(d)) != NULL) {
            if (strcmp(entree->d_name, ".") == 0 || strcmp(entree->d_name, "..") == 0) {
                continue;
            }

            char chemin_element[2048];
            snprintf(chemin_element, sizeof(chemin_element), "%s/%s", courant, entree->d_name);
            printf("%s\n", chemin_element);

            struct stat st;
            if (stat(chemin_element, &st) == 0 && S_ISDIR(st.st_mode)) {
                if (fin < MAX_QUEUE) {
                    strncpy(file_dossiers[fin++], chemin_element, PATH_LEN - 1);
                    file_dossiers[fin - 1][PATH_LEN - 1] = '\0';
                }
            }
        }

        closedir(d);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Utilisation : %s <nom_du_repertoire> [mode: 1=simple, 2=recursif, 3=iteratif]\n", argv[0]);
        return 1;
    }

    const char *nom_repertoire = argv[1];
    int mode = (argc >= 3) ? atoi(argv[2]) : 1;

    switch (mode) {
        case 1:
            lire_dossier(nom_repertoire);
            break;
        case 2:
            printf("--- Parcours récursif ---\n");
            lire_dossier_recursif(nom_repertoire);
            break;
        case 3:
            printf("--- Parcours itératif ---\n");
            lire_dossier_iteratif(nom_repertoire);
            break;
        default:
            printf("Mode non reconnu (%d). Modes valides : 1, 2, 3.\n", mode);
            break;
    }

    return 0;
}
