#include <stdio.h>

/**
 * Programme : etudiant.c
 * Description : Gestion des informations de 5 étudiant.e.s à l'aide de tableaux.
 *               Informations stockées : nom, prénom, adresse, note en Programmation C,
 *               note en Système d'exploitation.
 *               Parcours et accès avec la notation pointeur *(tableau + i).
 */

int main(void) {
    /* Tableaux contenant les noms et prénoms des étudiant.e.s */
    char noms[5][50] = {
        "Dupont",
        "Martin",
        "Durand",
        "Leroy",
        "Moreau"
    };

    char prenoms[5][50] = {
        "Marie",
        "Pierre",
        "Sophie",
        "Lucas",
        "Emma"
    };

    /* Tableau contenant les adresses */
    char adresses[5][100] = {
        "20, Boulevard Niels Bohr, Lyon",
        "22, Boulevard Niels Bohr, Lyon",
        "5, Rue Pasteur, Villeurbanne",
        "14, Avenue Jean Jaurès, Lyon",
        "8, Rue Bellecour, Lyon"
    };

    /* Tableaux contenant les notes des deux modules */
    float notes_prog[5] = {16.5f, 14.0f, 18.0f, 11.5f, 15.0f};
    float notes_sys[5] = {12.1f, 14.1f, 15.5f, 13.0f, 17.2f};

    /* Affichage des détails de chaque étudiant.e */
    for (int i = 0; i < 5; i++) {
        printf("Étudiant.e %d :\n", i + 1);
        printf("Nom : %s\n", *(noms + i));
        printf("Prénom : %s\n", *(prenoms + i));
        printf("Adresse : %s\n", *(adresses + i));
        printf("Note Programmation C : %.2f\n", *(notes_prog + i));
        printf("Note Système d'exploitation : %.2f\n", *(notes_sys + i));
        printf("\n");
    }

    return 0;
}
