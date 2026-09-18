#include <stdio.h>
#include <string.h>
#include "operator.h"
#include "fichier.h"
#include "liste.h"

/**
 * Programme : main.c
 * Description : Programme principal partagé par les exercices 4.1, 4.2 et 4.7.
 *               Une fonction d'entrée dédiée est définie pour chaque exercice,
 *               et l'utilisateur sélectionne l'exercice à exécuter.
 */

/* Fonction d'entrée pour l'exercice 4.1 : Calcul avec opérateurs */
void exercice4_1(void) {
    int num1 = 10;
    int num2 = 5;
    char op = '+';

    printf("--- Exercice 4.1 : Calcul avec opérateurs ---\n");
    printf("Entrez num1 : ");
    if (scanf("%d", &num1) != 1) {
        num1 = 10;
        printf("%d\n", num1);
    }

    printf("Entrez num2 : ");
    if (scanf("%d", &num2) != 1) {
        num2 = 5;
        printf("%d\n", num2);
    }

    printf("Entrez l'opérateur (+, -, *, /, %%, &, |, ~) : ");
    if (scanf(" %c", &op) != 1) {
        op = '+';
        printf("%c\n", op);
    }

    int res = calculer(op, num1, num2);
    printf("Résultat : %d\n", res);
}

/* Fonction d'entrée pour l'exercice 4.2 : Gestion de fichiers */
void exercice4_2(void) {
    int choix = 1;
    char nom_fichier[256];
    char message[256];

    printf("--- Exercice 4.2 : Gestion de fichiers ---\n");
    printf("Que souhaitez-vous faire ?\n");
    printf("1. Lire un fichier\n");
    printf("2. Écrire dans un fichier\n");
    printf("Votre choix : ");
    if (scanf("%d", &choix) != 1) {
        choix = 1;
        printf("%d\n", choix);
    }

    /* Nettoyage du tampon d'entrée */
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    if (choix == 1) {
        printf("Entrez le nom du fichier à lire : ");
        if (fgets(nom_fichier, sizeof(nom_fichier), stdin) != NULL) {
            nom_fichier[strcspn(nom_fichier, "\r\n")] = '\0';
        } else {
            strcpy(nom_fichier, "test.txt");
            printf("%s\n", nom_fichier);
        }
        lire_fichier(nom_fichier);
    } else if (choix == 2) {
        printf("Entrez le nom du fichier dans lequel vous souhaitez écrire : ");
        if (fgets(nom_fichier, sizeof(nom_fichier), stdin) != NULL) {
            nom_fichier[strcspn(nom_fichier, "\r\n")] = '\0';
        } else {
            strcpy(nom_fichier, "nouveau.txt");
            printf("%s\n", nom_fichier);
        }

        printf("Entrez le message à écrire : ");
        if (fgets(message, sizeof(message), stdin) != NULL) {
            message[strcspn(message, "\r\n")] = '\0';
        } else {
            strcpy(message, "Ceci est un message de test.");
            printf("%s\n", message);
        }
        ecrire_dans_fichier(nom_fichier, message);
    } else {
        printf("Choix invalide.\n");
    }
}

/* Fonction d'entrée pour l'exercice 4.7 : Gestion d'une liste de couleurs */
void exercice4_7(void) {
    printf("--- Exercice 4.7 : Gestion d'une liste de couleurs ---\n");
    struct liste_couleurs ma_liste;
    init_liste(&ma_liste);

    /* Définition et insertion de 10 couleurs RGBA */
    struct couleur couleurs[10] = {
        {0xFF, 0x00, 0x00, 0xFF}, /* Rouge */
        {0x00, 0xFF, 0x00, 0xFF}, /* Vert */
        {0x00, 0x00, 0xFF, 0xFF}, /* Bleu */
        {0xFF, 0xFF, 0x00, 0xFF}, /* Jaune */
        {0xFF, 0x00, 0xFF, 0xFF}, /* Magenta */
        {0x00, 0xFF, 0xFF, 0xFF}, /* Cyan */
        {0x80, 0x00, 0x00, 0xFF}, /* Marron */
        {0x80, 0x80, 0x80, 0xFF}, /* Gris */
        {0xFF, 0xA5, 0x00, 0xFF}, /* Orange */
        {0x80, 0x00, 0x80, 0xFF}  /* Violet */
    };

    for (int i = 0; i < 10; i++) {
        insertion(&couleurs[i], &ma_liste);
    }

    printf("Liste des couleurs :\n");
    parcours(&ma_liste);

    /* Libération de la mémoire allouée dynamiquement */
    liberer_liste(&ma_liste);
}

int main(void) {
    int choix = 0;

    printf("============================================\n");
    printf("      TP4 : Programme principal (main.c)    \n");
    printf("============================================\n");
    printf("Choisissez l'exercice à exécuter :\n");
    printf("1. Exercice 4.1 : Calcul avec opérateurs\n");
    printf("2. Exercice 4.2 : Gestion de fichiers\n");
    printf("3. Exercice 4.7 : Gestion d'une liste de couleurs\n");
    printf("Votre choix (1, 2 ou 3) : ");

    if (scanf("%d", &choix) != 1) {
        printf("1 (sélection par défaut)\n");
        choix = 1;
    }

    switch (choix) {
        case 1:
            exercice4_1();
            break;
        case 2:
            exercice4_2();
            break;
        case 3:
            exercice4_7();
            break;
        default:
            printf("Option non reconnue : %d\n", choix);
            break;
    }

    return 0;
}
