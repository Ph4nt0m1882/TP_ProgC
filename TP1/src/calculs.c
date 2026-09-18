#include <stdio.h>

int main(void) {
    int num1 = 12;
    int num2 = 5;
    char op = '&';

    switch (op) {
        /* Opérations arithmétiques */
        case '+':
            printf("%d + %d = %d\n", num1, num2, num1 + num2);
            break;

        case '-':
            printf("%d - %d = %d\n", num1, num2, num1 - num2);
            break;

        case '*':
            printf("%d * %d = %d\n", num1, num2, num1 * num2);
            break;

        case '/':
            if (num2 == 0) {
                printf("Erreur : division par zero impossible.\n");
            } else {
                printf("%d / %d = %d\n", num1, num2, num1 / num2);
            }
            break;

        case '%':
            if (num2 == 0) {
                printf("Erreur : modulo par zero impossible.\n");
            } else {
                printf("%d %% %d = %d\n", num1, num2, num1 % num2);
            }
            break;

        /* Opérations bit à bit (bitwise) */
        case '&':
            printf("%d & %d = %d\n", num1, num2, num1 & num2);
            break;

        case '|':
            printf("%d | %d = %d\n", num1, num2, num1 | num2);
            break;

        case '~':
            /* Opérateur unaire : inversion bit à bit */
            printf("~%d = %d\n", num1, ~num1);
            printf("~%d = %d\n", num2, ~num2);
            break;

        default:
            printf("Operateur '%c' non reconnu.\n", op);
            break;
    }

    return 0;
}
