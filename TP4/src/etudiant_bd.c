#include <stdio.h>
#include <string.h>
#include "fichier.h"

/**
 * Programme : etudiant_bd.c
 * Description : Enregistre les détails de 5 étudiant.e.s (nom, prénom, adresse, notes)
 *               dans un fichier texte "etudiant.txt" en réutilisant ecrire_dans_fichier.
 */

#define NB_ETUDIANTS 5

struct Etudiant {
    char nom[50];
    char prenom[50];
    char adresse[100];
    float note1;
    float note2;
};

int main(void) {
    struct Etudiant etudiants[NB_ETUDIANTS];
    char ligne[300];

    /* Réinitialisation du fichier cible */
    remove("etudiant.txt");

    /* Données d'exemple par défaut en cas d'exécution non-interactive */
    struct Etudiant defauts[NB_ETUDIANTS] = {
        {"Dupont", "Pierre", "Boulevard du 11 novembre 1918, Villeurbanne", 20.0f, 30.0f},
        {"Martin", "Marie", "Rue de la République, Lyon", 18.0f, 25.0f},
        {"Durand", "Sophie", "Avenue Jean Jaurès, Lyon", 17.5f, 28.0f},
        {"Leroy", "Lucas", "Place Bellecour, Lyon", 15.0f, 22.0f},
        {"Moreau", "Emma", "Rue Garibaldi, Lyon", 19.0f, 29.5f}
    };

    for (int i = 0; i < NB_ETUDIANTS; i++) {
        printf("Entrez les détails de l'étudiant.e %d :\n", i + 1);

        printf("Nom : ");
        if (scanf("%49s", etudiants[i].nom) != 1) {
            strcpy(etudiants[i].nom, defauts[i].nom);
            printf("%s\n", etudiants[i].nom);
        }

        printf("Prénom : ");
        if (scanf("%49s", etudiants[i].prenom) != 1) {
            strcpy(etudiants[i].prenom, defauts[i].prenom);
            printf("%s\n", etudiants[i].prenom);
        }

        /* Nettoyage du flux avant lecture de l'adresse (pouvant comporter des espaces) */
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        printf("Adresse : ");
        if (fgets(etudiants[i].adresse, sizeof(etudiants[i].adresse), stdin) != NULL) {
            etudiants[i].adresse[strcspn(etudiants[i].adresse, "\r\n")] = '\0';
            if (strlen(etudiants[i].adresse) == 0) {
                strcpy(etudiants[i].adresse, defauts[i].adresse);
            }
        } else {
            strcpy(etudiants[i].adresse, defauts[i].adresse);
            printf("%s\n", etudiants[i].adresse);
        }

        printf("Note 1 : ");
        if (scanf("%f", &etudiants[i].note1) != 1) {
            etudiants[i].note1 = defauts[i].note1;
            printf("%.1f\n", etudiants[i].note1);
        }

        printf("Note 2 : ");
        if (scanf("%f", &etudiants[i].note2) != 1) {
            etudiants[i].note2 = defauts[i].note2;
            printf("%.1f\n", etudiants[i].note2);
        }
        printf("\n");

        /* Formatage et écriture de l'étudiant.e dans le fichier */
        snprintf(ligne, sizeof(ligne),
                 "Nom : %s | Prénom : %s | Adresse : %s | Note 1 : %.2f | Note 2 : %.2f",
                 etudiants[i].nom,
                 etudiants[i].prenom,
                 etudiants[i].adresse,
                 etudiants[i].note1,
                 etudiants[i].note2);

        ecrire_dans_fichier("etudiant.txt", ligne);
    }

    printf("Les détails des étudiants ont été enregistrés dans le fichier etudiant.txt.\n");
    return 0;
}
