#include <stdio.h>

int main(void) {
    /* i. char */
    printf("char : %zu octet(s)\n", sizeof(char));
    printf("signed char : %zu octet(s)\n", sizeof(signed char));
    printf("unsigned char : %zu octet(s)\n", sizeof(unsigned char));

    /* ii. short */
    printf("short : %zu octet(s)\n", sizeof(short));
    printf("signed short : %zu octet(s)\n", sizeof(signed short));
    printf("unsigned short : %zu octet(s)\n", sizeof(unsigned short));

    /* iii. int */
    printf("int : %zu octet(s)\n", sizeof(int));
    printf("signed int : %zu octet(s)\n", sizeof(signed int));
    printf("unsigned int : %zu octet(s)\n", sizeof(unsigned int));

    /* iv. long int */
    printf("long int : %zu octet(s)\n", sizeof(long int));
    printf("signed long int : %zu octet(s)\n", sizeof(signed long int));
    printf("unsigned long int : %zu octet(s)\n", sizeof(unsigned long int));

    /* v. long long int */
    printf("long long int : %zu octet(s)\n", sizeof(long long int));
    printf("signed long long int : %zu octet(s)\n", sizeof(signed long long int));
    printf("unsigned long long int : %zu octet(s)\n", sizeof(unsigned long long int));

    /* vi. float */
    printf("float : %zu octet(s)\n", sizeof(float));

    /* vii. double */
    printf("double : %zu octet(s)\n", sizeof(double));

    /* viii. long double */
    printf("long double : %zu octet(s)\n", sizeof(long double));

    return 0;
}
