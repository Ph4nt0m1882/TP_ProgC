#include <stdio.h>

/**
 * Programme : puissance.c
 * Description : Calcule a élevé à la puissance b sans utiliser la fonction pow()
 *               de la bibliothèque <math.h> ni demander de saisie utilisateur.
 */

int main(void) {
    int a = 2;
    int b = 3;
    long long resultat = 1;

    /* Calcul de a^b avec une boucle */
    for (int i = 0; i < b; i++) {
        resultat *= a;
    }

    /* Affichage du résultat */
    printf("%d élevé à la puissance %d = %lld\n", a, b, resultat);

    return 0;
}
