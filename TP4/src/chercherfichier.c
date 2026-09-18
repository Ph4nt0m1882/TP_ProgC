#include <stdio.h>
#include <string.h>

/**
 * Programme : chercherfichier.c
 * Description : Recherche une phrase dans un fichier texte et affiche le numéro
 *               des lignes où elle apparaît ainsi que son nombre d'occurrences.
 *
 * Exemple :
 *   $ ./chercherfichier fichier.txt
 *   Entrez la phrase que vous souhaitez rechercher : exemple de phrase
 */

/* Fonction comptant les occurrences d'un motif dans une ligne */
static int compter_occurrences(const char *ligne, const char *motif) {
    if (ligne == NULL || motif == NULL || *motif == '\0') {
        return 0;
    }

    int compte = 0;
    size_t len_motif = strlen(motif);
    const char *p = ligne;

    while ((p = strstr(p, motif)) != NULL) {
        compte++;
        p += len_motif;
    }

    return compte;
}

int main(int argc, char *argv[]) {
    char nom_fichier[256];
    char phrase[256];

    /* Récupération du nom de fichier en argument ou par saisie */
    if (argc >= 2) {
        strncpy(nom_fichier, argv[1], sizeof(nom_fichier) - 1);
        nom_fichier[sizeof(nom_fichier) - 1] = '\0';
    } else {
        printf("Entrez le nom du fichier : ");
        if (fgets(nom_fichier, sizeof(nom_fichier), stdin) != NULL) {
            nom_fichier[strcspn(nom_fichier, "\r\n")] = '\0';
        } else {
            return 1;
        }
    }

    /* Demande de la phrase à rechercher */
    printf("Entrez la phrase que vous souhaitez rechercher : ");
    if (fgets(phrase, sizeof(phrase), stdin) != NULL) {
        phrase[strcspn(phrase, "\r\n")] = '\0';
    } else {
        return 1;
    }

    /* Ouverture du fichier */
    FILE *f = fopen(nom_fichier, "r");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier \"%s\".\n", nom_fichier);
        return 1;
    }

    printf("\nRésultats de la recherche :\n");

    char ligne[1024];
    int num_ligne = 1;
    int total_trouve = 0;

    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        int occ = compter_occurrences(ligne, phrase);
        if (occ > 0) {
            printf("Ligne %d, %d fois\n", num_ligne, occ);
            total_trouve += occ;
        }
        num_ligne++;
    }

    if (total_trouve == 0) {
        printf("La phrase n'a été trouvée dans aucune ligne.\n");
    }

    fclose(f);
    return 0;
}
