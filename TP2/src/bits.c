#include <stdio.h>

/**
 * Programme : bits.c
 * Description : Vérifie si le 4ème et le 20ème bit en partant de la gauche
 *               d'un entier d (sur 32 bits) sont tous deux à 1.
 *               Affiche 1 si c'est le cas, sinon 0.
 *               Toutes les instructions sont situées dans main().
 */

int main(void) {
    /* Valeur d'exemple ayant le 4ème et le 20ème bit de gauche à 1 */
    /* Sur 32 bits : 4ème bit de gauche = bit 28, 20ème bit de gauche = bit 12 */
    int d = (1 << 28) | (1 << 12);

    /* Détermination du nombre total de bits d'un entier */
    int nb_bits = sizeof(int) * 8;

    /* Extraction du 4ème bit depuis la gauche (position nb_bits - 4) */
    int bit4 = (d >> (nb_bits - 4)) & 1;

    /* Extraction du 20ème bit depuis la gauche (position nb_bits - 20) */
    int bit20 = (d >> (nb_bits - 20)) & 1;

    /* Vérification si les deux bits sont égaux à 1 */
    int resultat = 0;
    if (bit4 == 1 && bit20 == 1) {
        resultat = 1;
    }

    /* Affichage du résultat : 1 si les deux bits sont à 1, sinon 0 */
    printf("%d\n", resultat);

    return 0;
}
