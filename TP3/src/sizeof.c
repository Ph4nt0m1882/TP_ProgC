#include <stdio.h>

/**
 * Programme : sizeof.c
 * Description : Affiche la taille en octets de différents types de données
 *               et de leurs pointeurs sur une machine 64 bits.
 */

int main(void) {
    printf("La taille de int est : %zu octets\n", sizeof(int));
    printf("La taille de int* est : %zu octets\n", sizeof(int*));
    printf("La taille de int** est : %zu octets\n", sizeof(int**));
    printf("La taille de char* est : %zu octets\n", sizeof(char*));
    printf("La taille de char** est : %zu octets\n", sizeof(char**));
    printf("La taille de char*** est : %zu octets\n", sizeof(char***));
    printf("La taille de float* est : %zu octets\n", sizeof(float*));
    printf("La taille de float** est : %zu octets\n", sizeof(float**));
    printf("La taille de float*** est : %zu octets\n", sizeof(float***));

    return 0;
}
