#ifndef REPERTOIRE_H
#define REPERTOIRE_H

/**
 * En-tête : repertoire.h
 * Description : Déclarations des fonctions de parcours de répertoires
 *               (simple, récursif, itératif).
 */

/* Exercice 5.1 : Parcours simple d'un répertoire */
void lire_dossier(const char *nom_repertoire);

/* Exercice 5.2 : Parcours récursif d'un répertoire et ses sous-dossiers */
void lire_dossier_recursif(const char *nom_repertoire);

/* Exercice 5.3 : Parcours itératif d'un répertoire et ses sous-dossiers */
void lire_dossier_iteratif(const char *nom_repertoire);

#endif /* REPERTOIRE_H */
