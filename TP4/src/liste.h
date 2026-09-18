#ifndef LISTE_H
#define LISTE_H

/**
 * En-tête : liste.h
 * Description : Définition des structures de données et prototypes de fonctions
 *               pour gérer une liste simplement chaînée de couleurs RGBA.
 */

struct couleur {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

struct noeud {
    struct couleur couleur;
    struct noeud *suivant;
};

struct liste_couleurs {
    struct noeud *premier;
};

void init_liste(struct liste_couleurs *liste);
void insertion(const struct couleur *c, struct liste_couleurs *liste);
void parcours(const struct liste_couleurs *liste);
void liberer_liste(struct liste_couleurs *liste);

#endif /* LISTE_H */
