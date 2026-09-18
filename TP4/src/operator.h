#ifndef OPERATOR_H
#define OPERATOR_H

/**
 * En-tête : operator.h
 * Description : Déclarations des prototypes des fonctions d'opérations mathématiques
 *               et logiques pour les exercices 4.1 et 4.4.
 */

int somme(int num1, int num2);
int difference(int num1, int num2);
int produit(int num1, int num2);
int quotient(int num1, int num2);
int modulo(int num1, int num2);
int et(int num1, int num2);
int ou(int num1, int num2);
int negation(int num1, int num2);

/* Fonction générique exécutant l'opération selon le caractère op */
int calculer(char op, int num1, int num2);

#endif /* OPERATOR_H */
