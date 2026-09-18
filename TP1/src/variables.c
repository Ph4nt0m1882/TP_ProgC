#include <stdio.h>

int main(void) {
    /* i. char */
    char c = 'A';
    signed char sc = -65;
    unsigned char uc = 200U;

    printf("char : %c\n", c);
    printf("signed char : %d\n", sc);
    printf("unsigned char : %u\n", uc);

    /* ii. short */
    short s = -1234;
    signed short ss = -5678;
    unsigned short us = 50000U;

    printf("short : %d\n", s);
    printf("signed short : %d\n", ss);
    printf("unsigned short : %u\n", us);

    /* iii. int */
    int i = -42;
    signed int si = -100;
    unsigned int ui = 3000000000U;

    printf("int : %d\n", i);
    printf("signed int : %d\n", si);
    printf("unsigned int : %u\n", ui);

    /* iv. long int */
    long int li = -123456789L;
    signed long int sli = -987654321L;
    unsigned long int uli = 3000000000UL;

    printf("long int : %ld\n", li);
    printf("signed long int : %ld\n", sli);
    printf("unsigned long int : %lu\n", uli);

    /* v. long long int */
    long long int lli = -9000000000000000000LL;
    signed long long int slli = -123456789012345LL;
    unsigned long long int ulli = 18000000000000000000ULL;

    printf("long long int : %lld\n", lli);
    printf("signed long long int : %lld\n", slli);
    printf("unsigned long long int : %llu\n", ulli);

    /* vi. float */
    float f = 3.141592f;
    printf("float : %f\n", f);

    /* vii. double */
    double d = 2.7182818284;
    printf("double : %lf\n", d);

    /* viii. long double */
    long double ld = 1.618033988749894848L;
    printf("long double : %Lf\n", ld);

    return 0;
}