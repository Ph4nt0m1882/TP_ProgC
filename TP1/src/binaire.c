#include <stdio.h>

int main(void) {
    int nombres[] = {0, 4096, 65536, 65535, 1024};
    int total_nombres = sizeof(nombres) / sizeof(nombres[0]);
    int nb_bits = sizeof(int) * 8;

    for (int k = 0; k < total_nombres; k++) {
        int n = nombres[k];
        printf("%6d en binaire (32 bits) : ", n);

        for (int i = nb_bits - 1; i >= 0; i--) {
            int bit = (n >> i) & 1;
            printf("%d", bit);

            /* Espace tous les 4 bits pour faciliter la lecture */
            if (i % 4 == 0 && i != 0) {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}