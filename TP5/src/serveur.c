/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "serveur.h"

int socketfd = -1; // Déclaration globale de socketfd

/**
 * Cette fonction envoie un message (*data) au client (client_socket_fd)
 * @param client_socket_fd : Le descripteur de socket du client.
 * @param data : Le message à envoyer.
 * @return EXIT_SUCCESS en cas de succès, EXIT_FAILURE en cas d'erreur.
 */
int renvoie_message(int client_socket_fd, char *data)
{
  int data_size = write(client_socket_fd, (void *)data, strlen(data));

  if (data_size < 0)
  {
    perror("Erreur d'écriture");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

/**
 * Exercice 5.5 & 5.6 :
 * Cette fonction extrait l'opérateur et les opérandes, réalise le calcul,
 * et renvoie le résultat au client.
 */
int recois_numeros_calcule(int client_socket_fd, char *data)
{
  char op = 0;
  float num1 = 0.0f;
  float num2 = 0.0f;
  float resultat = 0.0f;
  char reponse[256];

  /* Format "calcule : <op> <num1> <num2>" */
  int matched = sscanf(data, "calcule : %c %f %f", &op, &num1, &num2);
  if (matched < 3)
  {
    /* Format direct "<op> <num1> <num2>" */
    matched = sscanf(data, "%c %f %f", &op, &num1, &num2);
  }

  if (matched >= 3)
  {
    switch (op)
    {
      case '+':
        resultat = num1 + num2;
        break;
      case '-':
        resultat = num1 - num2;
        break;
      case '*':
        resultat = num1 * num2;
        break;
      case '/':
        if (num2 == 0.0f)
        {
          snprintf(reponse, sizeof(reponse), "calcule : Erreur division par zéro\n");
          return renvoie_message(client_socket_fd, reponse);
        }
        resultat = num1 / num2;
        break;
      default:
        snprintf(reponse, sizeof(reponse), "calcule : Opérateur non supporté\n");
        return renvoie_message(client_socket_fd, reponse);
    }

    printf("Calcul effectué : %g %c %g = %g\n", num1, op, num2, resultat);
    snprintf(reponse, sizeof(reponse), "calcule : %g\n", resultat);
    return renvoie_message(client_socket_fd, reponse);
  }
  else
  {
    snprintf(reponse, sizeof(reponse), "calcule : format invalide\n");
    return renvoie_message(client_socket_fd, reponse);
  }
}

/**
 * Cette fonction lit les données envoyées par le client,
 * et renvoie un message ou résultat de calcul en réponse.
 * @param client_socket_fd : Le descripteur de socket du client.
 * @param data : Le message.
 * @return EXIT_SUCCESS en cas de succès, EXIT_FAILURE en cas d'erreur.
 */
int recois_envoie_message(int client_socket_fd, char *data)
{
  printf("Message reçu: %s", data);

  /* Traitement des requêtes de calcul */
  if (strncmp(data, "calcule :", 9) == 0 ||
      data[0] == '+' || data[0] == '-' || data[0] == '*' || data[0] == '/')
  {
    return recois_numeros_calcule(client_socket_fd, data);
  }

  /* Traitement des messages classiques "message: ..." */
  char code[10];
  if (sscanf(data, "%9s:", code) == 1)
  {
    if (strcmp(code, "message:") == 0)
    {
      return renvoie_message(client_socket_fd, data);
    }
  }

  return renvoie_message(client_socket_fd, data);
}

/**
 * Gestionnaire de signal pour Ctrl+C (SIGINT).
 * @param signal : Le signal capturé (doit être SIGINT pour Ctrl+C).
 */
void gestionnaire_ctrl_c(int signal)
{
  (void)signal; // Évite l'avertissement de paramètre inutilisé
  printf("\nSignal Ctrl+C capturé. Sortie du programme.\n");

  // Fermer le socket si ouvert
  if (socketfd != -1)
  {
    close(socketfd);
  }

  exit(0); // Quitter proprement le programme.
}

/**
 * Gère la communication avec un client spécifique.
 *
 * @param client_socket_fd Le descripteur de socket du client à gérer.
 */
void gerer_client(int client_socket_fd)
{
  char data[1024];

  while (1)
  {
    // Réinitialisation des données
    memset(data, 0, sizeof(data));

    // Lecture des données envoyées par le client
    int data_size = read(client_socket_fd, data, sizeof(data));

    if (data_size <= 0)
    {
      // Erreur de réception ou déconnexion du client
      if (data_size == 0)
      {
        printf("Client déconnecté.\n");
      }
      else
      {
        perror("Erreur de réception");
      }

      close(client_socket_fd);
      break;
    }

    recois_envoie_message(client_socket_fd, data);
  }
}

/**
 * Configuration du serveur socket et attente de connexions.
 */
int main(void)
{
  int bind_status;
  struct sockaddr_in server_addr;
  int option = 1;

  // Création d'une socket
  socketfd = socket(AF_INET, SOCK_STREAM, 0);

  if (socketfd < 0)
  {
    perror("Impossible d'ouvrir une socket");
    return -1;
  }

  // Configuration de l'option SO_REUSEADDR
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  // Initialisation de la structure server_addr
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // Liaison de l'adresse à la socket
  bind_status = bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  if (bind_status < 0)
  {
    perror("bind");
    return (EXIT_FAILURE);
  }

  // Enregistrement de la fonction de gestion du signal Ctrl+C
  signal(SIGINT, gestionnaire_ctrl_c);

  // Mise en attente de connexions
  listen(socketfd, 10);

  printf("Serveur en attente de connexions...\n");

  struct sockaddr_in client_addr;
  unsigned int client_addr_len = sizeof(client_addr);
  int client_socket_fd;

  while (1)
  {
    client_socket_fd = accept(socketfd, (struct sockaddr *)&client_addr, &client_addr_len);

    if (client_socket_fd < 0)
    {
      perror("accept");
      continue;
    }

    pid_t child_pid = fork();

    if (child_pid == 0)
    {
      // Processus enfant
      close(socketfd);
      gerer_client(client_socket_fd);
      exit(0);
    }
    else if (child_pid < 0)
    {
      perror("fork");
      close(client_socket_fd);
    }
    else
    {
      // Processus parent
      close(client_socket_fd);
    }
  }

  return 0;
}
