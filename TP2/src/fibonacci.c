#include <stdio.h>

/**
 * Programme : fibonacci.c
 * Description : Génère et affiche les n premiers termes de la suite de Fibonacci :
 *               U0 = 0, U1 = 1, Un = Un-1 + Un-2.
 */

int main(void) {
    int n = 7; /* Nombre de termes à afficher */
    long long u0 = 0;
    long long u1 = 1;

    printf("Suite de Fibonacci pour n = %d :\n", n);

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            printf("%lld", u0);
        } else if (i == 1) {
            printf(", %lld", u1);
        } else {
            long long un = u0 + u1;
            printf(", %lld", un);
            u0 = u1;
            u1 = un;
        }
    }
    printf("\n");

    return 0;
}
