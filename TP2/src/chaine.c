#include <stdio.h>

/**
 * Programme : chaine.c
 * Description : Effectue 3 opérations sur les chaînes de caractères sans
 *               utiliser la bibliothèque <string.h> ni d'autre bibliothèque externe :
 *               1. Calcul de la longueur d'une chaîne.
 *               2. Copie d'une chaîne dans une autre.
 *               3. Concaténation de deux chaînes de caractères.
 */

int main(void) {
    char str1[] = "Hello";
    char str2[] = " World!";
    char copie[100];
    char concat[100];

    /* 1. Calcul de la longueur de str1 */
    int len1 = 0;
    while (str1[len1] != '\0') {
        len1++;
    }

    /* Calcul de la longueur de str2 */
    int len2 = 0;
    while (str2[len2] != '\0') {
        len2++;
    }

    printf("Longueur de str1 (\"%s\") : %d\n", str1, len1);
    printf("Longueur de str2 (\"%s\") : %d\n", str2, len2);

    /* 2. Copie de str1 dans 'copie' */
    int i = 0;
    while (str1[i] != '\0') {
        copie[i] = str1[i];
        i++;
    }
    copie[i] = '\0';

    printf("Copie de str1 : \"%s\"\n", copie);

    /* 3. Concaténation de str1 et str2 dans 'concat' */
    int k = 0;
    while (str1[k] != '\0') {
        concat[k] = str1[k];
        k++;
    }
    int j = 0;
    while (str2[j] != '\0') {
        concat[k] = str2[j];
        k++;
        j++;
    }
    concat[k] = '\0';

    /* Calcul de la longueur de la chaîne concaténée */
    int len_concat = 0;
    while (concat[len_concat] != '\0') {
        len_concat++;
    }

    printf("Concaténation de str1 et str2 : \"%s\"\n", concat);
    printf("Longueur totale de la chaîne concaténée : %d\n", len_concat);

    return 0;
}
