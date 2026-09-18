#include <stdio.h>
#include <string.h>

/**
 * Programme : ptrvariables.c
 * Description : Manipulation de variables de types de base (char, short, int,
 *               long int, long long int, float, double, long double) via des pointeurs.
 *               Affiche l'adresse (%p) et la valeur en hexadécimal de chaque variable
 *               avant et après modification par son pointeur.
 */

int main(void) {
    /* Déclaration et initialisation des variables de base */
    char c = 0x41;                     /* 'A' */
    short s = 0x1234;
    int i = 0xa47865ff;
    long int l = 0x12345678L;
    long long int ll = 0x0123456789abcdefLL;
    float f = 2.0f;                    /* 0x40000000 en IEEE 754 */
    double d = 2.0;
    long double ld = 2.0L;

    /* Déclaration des pointeurs associés */
    char *pc = &c;
    short *ps = &s;
    int *pi = &i;
    long int *pl = &l;
    long long int *pll = &ll;
    float *pf = &f;
    double *pd = &d;
    long double *pld = &ld;

    /* Variables temporaires pour extraire la représentation binaire des flottants */
    unsigned int f_raw;
    unsigned long long d_raw;
    unsigned char ld_raw[sizeof(long double)];

    /* --- Avant la manipulation --- */
    printf("Avant la manipulation :\n");
    printf("Adresse de c : %p, Valeur de c : %02x\n", (void *)pc, (unsigned char)*pc);
    printf("Adresse de s : %p, Valeur de s : %04x\n", (void *)ps, (unsigned short)*ps);
    printf("Adresse de i : %p, Valeur de i : %x\n", (void *)pi, (unsigned int)*pi);
    printf("Adresse de l : %p, Valeur de l : %lx\n", (void *)pl, (unsigned long)*pl);
    printf("Adresse de ll : %p, Valeur de ll : %llx\n", (void *)pll, (unsigned long long)*pll);

    memcpy(&f_raw, pf, sizeof(float));
    printf("Adresse de f : %p, Valeur de f : %08x\n", (void *)pf, f_raw);

    memcpy(&d_raw, pd, sizeof(double));
    printf("Adresse de d : %p, Valeur de d : %016llx\n", (void *)pd, d_raw);

    memcpy(ld_raw, pld, sizeof(long double));
    printf("Adresse de ld : %p, Valeur de ld : ", (void *)pld);
    for (int k = (int)sizeof(long double) - 1; k >= 0; k--) {
        printf("%02x", ld_raw[k]);
    }
    printf("\n\n");

    /* --- Manipulation via les pointeurs --- */
    *pc = 0x42;         /* 'B' */
    *ps = 0x4321;
    *pi = 0xa47865fe;
    *pl = 0x87654321L;
    *pll = 0xfedcba9876543210LL;
    *pf = 1.0f;         /* 0x3f800000 en IEEE 754 */
    *pd = 1.0;
    *pld = 1.0L;

    /* --- Après la manipulation --- */
    printf("Après la manipulation :\n");
    printf("Adresse de c : %p, Valeur de c : %02x\n", (void *)pc, (unsigned char)*pc);
    printf("Adresse de s : %p, Valeur de s : %04x\n", (void *)ps, (unsigned short)*ps);
    printf("Adresse de i : %p, Valeur de i : %x\n", (void *)pi, (unsigned int)*pi);
    printf("Adresse de l : %p, Valeur de l : %lx\n", (void *)pl, (unsigned long)*pl);
    printf("Adresse de ll : %p, Valeur de ll : %llx\n", (void *)pll, (unsigned long long)*pll);

    memcpy(&f_raw, pf, sizeof(float));
    printf("Adresse de f : %p, Valeur de f : %08x\n", (void *)pf, f_raw);

    memcpy(&d_raw, pd, sizeof(double));
    printf("Adresse de d : %p, Valeur de d : %016llx\n", (void *)pd, d_raw);

    memcpy(ld_raw, pld, sizeof(long double));
    printf("Adresse de ld : %p, Valeur de ld : ", (void *)pld);
    for (int k = (int)sizeof(long double) - 1; k >= 0; k--) {
        printf("%02x", ld_raw[k]);
    }
    printf("\n");

    return 0;
}
