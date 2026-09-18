#ifndef FICHIER_H
#define FICHIER_H

/**
 * En-tête : fichier.h
 * Description : Déclarations des prototypes des fonctions de gestion de fichiers.
 */

int lire_fichier(const char *nom_de_fichier);
int ecrire_dans_fichier(const char *nom_de_fichier, const char *message);

#endif /* FICHIER_H */
