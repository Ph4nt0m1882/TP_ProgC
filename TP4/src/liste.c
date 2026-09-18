#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

/**
 * Fichier source : liste.c
 * Description : Implémentation des opérations sur la liste chaînée de couleurs RGBA :
 *               initialisation, insertion en queue, parcours et libération mémoire.
 */

void init_liste(struct liste_couleurs *liste) {
    if (liste != NULL) {
        liste->premier = NULL;
    }
}

void insertion(const struct couleur *c, struct liste_couleurs *liste) {
    if (liste == NULL || c == NULL) {
        return;
    }

    struct noeud *nouveau = (struct noeud *)malloc(sizeof(struct noeud));
    if (nouveau == NULL) {
        printf("Erreur : Échec de l'allocation mémoire pour le nouveau nœud.\n");
        return;
    }

    nouveau->couleur = *c;
    nouveau->suivant = NULL;

    /* Insertion en fin de liste pour conserver l'ordre d'ajout */
    if (liste->premier == NULL) {
        liste->premier = nouveau;
    } else {
        struct noeud *courant = liste->premier;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }
        courant->suivant = nouveau;
    }
}

void parcours(const struct liste_couleurs *liste) {
    if (liste == NULL || liste->premier == NULL) {
        printf("La liste est vide.\n");
        return;
    }

    const struct noeud *courant = liste->premier;
    int index = 1;
    while (courant != NULL) {
        printf("Couleur %2d : (R=%u, G=%u, B=%u, A=%u) [0x%02x 0x%02x 0x%02x 0x%02x]\n",
               index++,
               courant->couleur.r,
               courant->couleur.g,
               courant->couleur.b,
               courant->couleur.a,
               courant->couleur.r,
               courant->couleur.g,
               courant->couleur.b,
               courant->couleur.a);
        courant = courant->suivant;
    }
}

void liberer_liste(struct liste_couleurs *liste) {
    if (liste == NULL) {
        return;
    }

    struct noeud *courant = liste->premier;
    while (courant != NULL) {
        struct noeud *temp = courant;
        courant = courant->suivant;
        free(temp);
    }
    liste->premier = NULL;
}
