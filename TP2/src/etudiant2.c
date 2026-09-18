#include <stdio.h>
#include <string.h>

/**
 * Programme : etudiant2.c
 * Description : Gestion des informations de 5 étudiant.e.s en utilisant une
 *               structure (struct) et la fonction strcpy pour l'initialisation.
 */

/* Définition de la structure représentant un.e étudiant.e */
struct Etudiant {
    char nom[50];
    char prenom[50];
    char adresse[100];
    float note1;
    float note2;
};

int main(void) {
    /* Tableau de 5 structures */
    struct Etudiant etudiants[5];

    /* Initialisation de l'étudiant.e 1 */
    strcpy(etudiants[0].nom, "Dupont");
    strcpy(etudiants[0].prenom, "Marie");
    strcpy(etudiants[0].adresse, "20, Boulevard Niels Bohr, Lyon");
    etudiants[0].note1 = 16.5f;
    etudiants[0].note2 = 12.1f;

    /* Initialisation de l'étudiant.e 2 */
    strcpy(etudiants[1].nom, "Martin");
    strcpy(etudiants[1].prenom, "Pierre");
    strcpy(etudiants[1].adresse, "22, Boulevard Niels Bohr, Lyon");
    etudiants[1].note1 = 14.0f;
    etudiants[1].note2 = 14.1f;

    /* Initialisation de l'étudiant.e 3 */
    strcpy(etudiants[2].nom, "Durand");
    strcpy(etudiants[2].prenom, "Sophie");
    strcpy(etudiants[2].adresse, "5, Rue Pasteur, Villeurbanne");
    etudiants[2].note1 = 18.0f;
    etudiants[2].note2 = 15.5f;

    /* Initialisation de l'étudiant.e 4 */
    strcpy(etudiants[3].nom, "Leroy");
    strcpy(etudiants[3].prenom, "Lucas");
    strcpy(etudiants[3].adresse, "14, Avenue Jean Jaurès, Lyon");
    etudiants[3].note1 = 11.5f;
    etudiants[3].note2 = 13.0f;

    /* Initialisation de l'étudiant.e 5 */
    strcpy(etudiants[4].nom, "Moreau");
    strcpy(etudiants[4].prenom, "Emma");
    strcpy(etudiants[4].adresse, "8, Rue Bellecour, Lyon");
    etudiants[4].note1 = 15.0f;
    etudiants[4].note2 = 17.2f;

    /* Affichage des données des étudiant.e.s */
    for (int i = 0; i < 5; i++) {
        printf("Étudiant.e %d :\n", i + 1);
        printf("Nom : %s\n", etudiants[i].nom);
        printf("Prénom : %s\n", etudiants[i].prenom);
        printf("Adresse : %s\n", etudiants[i].adresse);
        printf("Note 1 : %.1f\n", etudiants[i].note1);
        printf("Note 2 : %.1f\n", etudiants[i].note2);
        printf("\n");
    }

    return 0;
}
