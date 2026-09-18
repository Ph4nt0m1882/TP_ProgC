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
#include "bmp.h"

/**
 * Exercice 6.3 :
 * Envoi et réception d'un message textuel au format JSON.
 */
int envoie_recois_message(int socketfd)
{
  char data[2048];
  char message[1000];

  memset(data, 0, sizeof(data));

  printf("Votre message (max 1000 caractères) : ");
  if (fgets(message, sizeof(message), stdin) == NULL)
  {
    return -1;
  }

  /* Retrait du saut de ligne éventuel */
  message[strcspn(message, "\r\n")] = '\0';

  /* Construction du message au format JSON */
  snprintf(data, sizeof(data),
           "{\n  \"code\": \"message\",\n  \"valeurs\": [\"%s\"]\n}\n",
           message);

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("erreur écriture");
    return -1;
  }

  memset(data, 0, sizeof(data));
  int read_status = read(socketfd, data, sizeof(data) - 1);
  if (read_status < 0)
  {
    perror("erreur lecture");
    return -1;
  }

  printf("Message reçu : %s\n", data);
  return 0;
}

/**
 * Exercice 6.1, 6.2 et 6.3 :
 * Analyse d'une image BMP, extraction d'un nombre paramétrable de couleurs (<= 30)
 * et formatage du message sous forme JSON.
 */
void analyse(char *pathname, char *data, int max_couleurs)
{
  couleur_compteur *cc = analyse_bmp_image(pathname);
  if (cc == NULL)
  {
    snprintf(data, 2048, "{\n  \"code\": \"erreur\",\n  \"valeurs\": [\"fichier_invalide\"]\n}\n");
    return;
  }

  /* Validation du nombre de couleurs (1 à 30, par défaut 10) */
  int nb = max_couleurs;
  if (nb <= 0 || nb > 30)
  {
    nb = 10;
  }
  if (cc->size < nb)
  {
    nb = cc->size;
  }

  /* Début du JSON */
  strcpy(data, "{\n  \"code\": \"couleurs\",\n  \"valeurs\": [");

  char hex[32];
  for (int count = 1; count <= nb && (cc->size - count) >= 0; count++)
  {
    int index = cc->size - count;
    if (cc->compte_bit == BITS32)
    {
      snprintf(hex, sizeof(hex), "\"#%02x%02x%02x\"",
               cc->cc.cc32[index].c.rouge,
               cc->cc.cc32[index].c.vert,
               cc->cc.cc32[index].c.bleu);
    }
    else
    {
      snprintf(hex, sizeof(hex), "\"#%02x%02x%02x\"",
               cc->cc.cc24[index].c.rouge,
               cc->cc.cc24[index].c.vert,
               cc->cc.cc24[index].c.bleu);
    }

    strcat(data, hex);
    if (count < nb)
    {
      strcat(data, ", ");
    }
  }

  strcat(data, "]\n}\n");
}

int envoie_couleurs(int socketfd, char *pathname, int nb_couleurs)
{
  char data[2048];
  memset(data, 0, sizeof(data));

  analyse(pathname, data, nb_couleurs);

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("erreur écriture");
    return -1;
  }

  memset(data, 0, sizeof(data));
  int read_status = read(socketfd, data, sizeof(data) - 1);
  if (read_status > 0)
  {
    printf("Réponse du serveur :\n%s\n", data);
  }

  return 0;
}

int main(int argc, char **argv)
{
  int socketfd;
  struct sockaddr_in server_addr;

  if (argc < 2)
  {
    printf("Usage : %s <chemin_image_bmp> [nb_couleurs (<= 30)]\n", argv[0]);
    printf("   ou : %s -m  (mode message textuel)\n", argv[0]);
    return EXIT_FAILURE;
  }

  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("socket");
    return EXIT_FAILURE;
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  int connect_status = connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (connect_status < 0)
  {
    perror("connection serveur");
    close(socketfd);
    return EXIT_FAILURE;
  }

  if (strcmp(argv[1], "-m") == 0)
  {
    /* Mode message interactif */
    envoie_recois_message(socketfd);
  }
  else
  {
    /* Mode analyse d'image avec nombre de couleurs spécifié ou par défaut 10 */
    int nb_couleurs = 10;
    if (argc >= 3)
    {
      nb_couleurs = atoi(argv[2]);
      if (nb_couleurs <= 0 || nb_couleurs > 30)
      {
        printf("Nombre de couleurs ajusté à 10 (doit être entre 1 et 30).\n");
        nb_couleurs = 10;
      }
    }

    printf("Analyse de l'image \"%s\" avec %d couleurs...\n", argv[1], nb_couleurs);
    envoie_couleurs(socketfd, argv[1], nb_couleurs);
  }

  close(socketfd);
  return EXIT_SUCCESS;
}
