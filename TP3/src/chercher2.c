#include <stdio.h>

/**
 * Programme : chercher2.c
 * Description : Tableau de 10 phrases. Recherche manuelle d'une phrase cible
 *               en comparant les caractères un par un sans utiliser de bibliothèque
 *               standard (pas de strcmp, etc.).
 */

#define NB_PHRASES 10

/* Fonction de comparaison caractère par caractère sans bibliothèque */
static int phrases_egales(const char *s1, const char *s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return 0;
        }
        i++;
    }
    return (s1[i] == '\0' && s2[i] == '\0');
}

/* Fonction de recherche d'une phrase dans le tableau */
static void rechercher_phrase(const char *tableau[], int taille, const char *cible) {
    int trouve = 0;
    for (int i = 0; i < taille; i++) {
        if (phrases_egales(tableau[i], cible)) {
            trouve = 1;
            break;
        }
    }

    printf("Recherche de : \"%s\"\n", cible);
    if (trouve) {
        printf("Phrase trouvée\n");
    } else {
        printf("Phrase non trouvée\n");
    }
}

int main(void) {
    const char *phrases[NB_PHRASES] = {
        "Bonjour, comment ça va ?",
        "Le temps est magnifique aujourd'hui.",
        "C'est une belle journée.",
        "La programmation en C est amusante.",
        "Les tableaux en C sont puissants.",
        "Les pointeurs en C peuvent être déroutants.",
        "Il fait beau dehors.",
        "La recherche dans un tableau est intéressante.",
        "Les structures de données sont importantes.",
        "Programmer en C, c'est génial."
    };

    /* Test 1 : Phrase présente */
    rechercher_phrase(phrases, NB_PHRASES, "La programmation en C est amusante.");
    printf("\n");

    /* Test 2 : Phrase absente */
    rechercher_phrase(phrases, NB_PHRASES, "Je préfère le Python.");

    return 0;
}
