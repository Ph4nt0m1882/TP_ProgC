#include <stdio.h>

/**
 * Programme : couleurs.c
 * Description : Représentation de 10 couleurs au format RGBA (rouge, vert, bleu, alpha)
 *               avec une structure (struct). Chaque composant est un octet (unsigned char),
 *               initialisé en notation hexadécimale, et affiché en décimal.
 */

/* Définition de la structure RGBA */
struct Couleur {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

int main(void) {
    /* Initialisation de 10 couleurs en notation hexadécimale */
    struct Couleur couleurs[10] = {
        {0xef, 0x78, 0x12, 0xff}, /* Couleur 1 : Rouge 239, Vert 120, Bleu 18, Alpha 255 */
        {0x2c, 0xc8, 0x64, 0xff}, /* Couleur 2 : Rouge 44, Vert 200, Bleu 100, Alpha 255 */
        {0xff, 0x00, 0x00, 0xff}, /* Rouge pur */
        {0x00, 0xff, 0x00, 0xff}, /* Vert pur */
        {0x00, 0x00, 0xff, 0xff}, /* Bleu pur */
        {0xff, 0xff, 0x00, 0xcc}, /* Jaune */
        {0x80, 0x00, 0x80, 0x99}, /* Violet */
        {0x00, 0x80, 0x80, 0x80}, /* Sarcelle (Teal) */
        {0xff, 0xa5, 0x00, 0xff}, /* Orange */
        {0xff, 0xff, 0xff, 0x00}  /* Blanc transparent */
    };

    /* Affichage des détails des 10 couleurs */
    for (int i = 0; i < 10; i++) {
        printf("Couleur %d :\n", i + 1);
        printf("Rouge : %u\n", couleurs[i].r);
        printf("Vert : %u\n", couleurs[i].g);
        printf("Bleu : %u\n", couleurs[i].b);
        printf("Alpha : %u\n", couleurs[i].a);
        printf("\n");
    }

    return 0;
}
