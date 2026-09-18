/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "client.h"

/**
 * Exercice 5.5 :
 * Envoie une opération arithmétique au serveur et affiche le résultat reçu.
 */
int envoie_operateur_numeros(int socketfd, char op, float num1, float num2)
{
  char data[1024];
  memset(data, 0, sizeof(data));

  snprintf(data, sizeof(data), "calcule : %c %g %g\n", op, num1, num2);

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("Erreur d'écriture");
    return -1;
  }

  memset(data, 0, sizeof(data));
  int read_status = read(socketfd, data, sizeof(data) - 1);
  if (read_status < 0)
  {
    perror("Erreur de lecture");
    return -1;
  }

  printf("Message reçu: %s", data);
  return 0;
}

/**
 * Exercice 5.6 :
 * Lit les notes des étudiants à partir des fichiers et délègue les calculs au serveur.
 */
static float lire_note_fichier(const char *chemin)
{
  FILE *f = fopen(chemin, "r");
  if (f == NULL)
  {
    return 0.0f;
  }
  float note = 0.0f;
  if (fscanf(f, "%f", &note) != 1)
  {
    note = 0.0f;
  }
  fclose(f);
  return note;
}

static float demander_calcul_serveur(int socketfd, char op, float n1, float n2)
{
  char buffer[1024];
  memset(buffer, 0, sizeof(buffer));
  snprintf(buffer, sizeof(buffer), "calcule : %c %g %g\n", op, n1, n2);
  if (write(socketfd, buffer, strlen(buffer)) < 0) return 0.0f;

  memset(buffer, 0, sizeof(buffer));
  if (read(socketfd, buffer, sizeof(buffer) - 1) <= 0) return 0.0f;

  float resultat = 0.0f;
  sscanf(buffer, "calcule : %f", &resultat);
  return resultat;
}

void calculer_notes_etudiants(int socketfd)
{
  printf("\n=== Calcul des notes des étudiants via le serveur ===\n");
  float total_toutes_notes = 0.0f;
  int nb_notes_total = 0;

  for (int e = 1; e <= 5; e++)
  {
    float somme_etudiant = 0.0f;
    for (int n = 1; n <= 5; n++)
    {
      char chemin[256];
      snprintf(chemin, sizeof(chemin), "etudiant/%d/note%d.txt", e, n);
      FILE *test = fopen(chemin, "r");
      if (test == NULL)
      {
        /* Essai avec chemin parent */
        snprintf(chemin, sizeof(chemin), "../etudiant/%d/note%d.txt", e, n);
      }
      else
      {
        fclose(test);
      }

      float note = lire_note_fichier(chemin);
      somme_etudiant = demander_calcul_serveur(socketfd, '+', somme_etudiant, note);
      nb_notes_total++;
    }

    float moyenne_etudiant = demander_calcul_serveur(socketfd, '/', somme_etudiant, 5.0f);
    printf("Étudiant %d - Somme des notes : %.2f, Moyenne : %.2f\n", e, somme_etudiant, moyenne_etudiant);
    total_toutes_notes = demander_calcul_serveur(socketfd, '+', total_toutes_notes, somme_etudiant);
  }

  if (nb_notes_total > 0)
  {
    float moyenne_classe = demander_calcul_serveur(socketfd, '/', total_toutes_notes, (float)nb_notes_total);
    printf("Moyenne générale de la classe : %.2f\n", moyenne_classe);
  }
}

/**
 * Fonction pour envoyer et recevoir un message depuis un client connecté à la socket.
 */
int envoie_recois_message(int socketfd)
{
  char data[2048];
  char message[1000];

  memset(data, 0, sizeof(data));

  printf("Votre message (max 1000 caractères, ou 'calcule : <op> <n1> <n2>', ou 'notes'): ");
  if (fgets(message, sizeof(message), stdin) == NULL)
  {
    return -1;
  }

  /* Retrait du saut de ligne final */
  message[strcspn(message, "\r\n")] = '\0';

  if (strlen(message) == 0)
  {
    return 0;
  }

  if (strcmp(message, "notes") == 0)
  {
    calculer_notes_etudiants(socketfd);
    return 0;
  }

  char op;
  float n1, n2;
  if (sscanf(message, "calcule : %c %f %f", &op, &n1, &n2) == 3 ||
      sscanf(message, "%c %f %f", &op, &n1, &n2) == 3)
  {
    return envoie_operateur_numeros(socketfd, op, n1, n2);
  }

  /* Message texte classique */
  snprintf(data, sizeof(data), "message: %s\n", message);

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("Erreur d'écriture");
    return -1;
  }

  memset(data, 0, sizeof(data));
  int read_status = read(socketfd, data, sizeof(data) - 1);
  if (read_status < 0)
  {
    perror("Erreur de lecture");
    return -1;
  }

  printf("Message reçu: %s", data);
  return 0;
}

int main(int argc, char *argv[])
{
  int socketfd;
  struct sockaddr_in server_addr;

  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  int connect_status = connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (connect_status < 0)
  {
    perror("connection serveur");
    exit(EXIT_FAILURE);
  }

  if (argc >= 4)
  {
    /* Exécution en ligne de commande : ./client <op> <num1> <num2> */
    char op = argv[1][0];
    float num1 = (float)atof(argv[2]);
    float num2 = (float)atof(argv[3]);
    envoie_operateur_numeros(socketfd, op, num1, num2);
  }
  else if (argc == 2 && strcmp(argv[1], "notes") == 0)
  {
    calculer_notes_etudiants(socketfd);
  }
  else
  {
    while (1)
    {
      if (envoie_recois_message(socketfd) < 0)
      {
        break;
      }
    }
  }

  close(socketfd);
  return 0;
}
