#include <stdio.h>

/**
 * Programme : octets.c
 * Description : Utilise des pointeurs (unsigned char *) pour afficher les octets
 *               individuels en mémoire de variables de types :
 *               short, int, long int, float, double, long double.
 */

int main(void) {
    /* Déclaration et initialisation des variables */
    short s = 0x0302;
    int i = 0x04030201;
    long int l = 0x0807060504030201L;
    float f = 12.34f;
    double d = 1.0;
    long double ld = 1.0L;

    /* Pointeur pour parcourir la mémoire octet par octet */
    unsigned char *p;

    /* Octets de short */
    printf("Octets de short :\n");
    p = (unsigned char *)&s;
    for (size_t k = 0; k < sizeof(short); k++) {
        printf(" %02x", *(p + k));
    }
    printf("\n\n");

    /* Octets de int */
    printf("Octets de int :\n");
    p = (unsigned char *)&i;
    for (size_t k = 0; k < sizeof(int); k++) {
        printf(" %02x", *(p + k));
    }
    printf("\n\n");

    /* Octets de long int */
    printf("Octets de long int :\n");
    p = (unsigned char *)&l;
    for (size_t k = 0; k < sizeof(long int); k++) {
        printf(" %02x", *(p + k));
    }
    printf("\n\n");

    /* Octets de float */
    printf("Octets de float :\n");
    p = (unsigned char *)&f;
    for (size_t k = 0; k < sizeof(float); k++) {
        printf(" %02x", *(p + k));
    }
    printf("\n\n");

    /* Octets de double */
    printf("Octets de double :\n");
    p = (unsigned char *)&d;
    for (size_t k = 0; k < sizeof(double); k++) {
        printf(" %02x", *(p + k));
    }
    printf("\n\n");

    /* Octets de long double */
    printf("Octets de long double :\n");
    p = (unsigned char *)&ld;
    for (size_t k = 0; k < sizeof(long double); k++) {
        printf(" %02x", *(p + k));
    }
    printf("\n");

    return 0;
}
