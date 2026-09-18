/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <math.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "serveur.h"

int socketfd = -1;

int visualize_plot(void)
{
  const char *browser = "firefox";

  char command[256];
  snprintf(command, sizeof(command), "%s %s 2>/dev/null", browser, SVG_FILE_PATH);

  int result = system(command);

  if (result == 0)
  {
    printf("Fichier SVG ouvert dans %s.\n", browser);
  }
  else
  {
    printf("Diagramme SVG généré dans \"%s\".\n", SVG_FILE_PATH);
  }

  return 0;
}

double degreesToRadians(double degrees)
{
  return degrees * M_PI / 180.0;
}

/**
 * Exercice 6.1 & 6.2 :
 * Génère un graphique SVG camembert avec un nombre paramétrable de couleurs (<= 30).
 */
int plot_colors(char colors[][16], int num_colors)
{
  if (num_colors <= 0)
  {
    return 1;
  }

  FILE *svg_file = fopen(SVG_FILE_PATH, "w");
  if (svg_file == NULL)
  {
    perror("Erreur lors de l'ouverture du fichier SVG");
    return 1;
  }

  fprintf(svg_file, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
  fprintf(svg_file, "<svg width=\"400\" height=\"400\" xmlns=\"http://www.w3.org/2000/svg\">\n");
  fprintf(svg_file, "  <rect width=\"100%%\" height=\"100%%\" fill=\"#ffffff\" />\n");

  double center_x = 200.0;
  double center_y = 200.0;
  double radius = 150.0;
  double start_angle = -90.0;
  double slice_angle = 360.0 / (double)num_colors;

  for (int i = 0; i < num_colors; i++)
  {
    double end_angle = start_angle + slice_angle;

    double start_angle_rad = degreesToRadians(start_angle);
    double end_angle_rad = degreesToRadians(end_angle);

    double x1 = center_x + radius * cos(start_angle_rad);
    double y1 = center_y + radius * sin(start_angle_rad);
    double x2 = center_x + radius * cos(end_angle_rad);
    double y2 = center_y + radius * sin(end_angle_rad);

    fprintf(svg_file, "  <path d=\"M%.2f,%.2f A%.2f,%.2f 0 0,1 %.2f,%.2f L%.2f,%.2f Z\" fill=\"%s\" />\n",
            x1, y1, radius, radius, x2, y2, center_x, center_y, colors[i]);

    start_angle = end_angle;
  }

  fprintf(svg_file, "</svg>\n");
  fclose(svg_file);

  visualize_plot();
  return 0;
}

/**
 * Traite les données de couleurs au format texte ou CSV.
 */
int plot(char *data)
{
  char colors[32][16];
  int num_colors = 0;

  char *saveptr = NULL;
  char *token = strtok_r(data, ",", &saveptr);

  /* Le premier jeton peut contenir le nombre de couleurs (ex: "couleurs: 10" ou "10") */
  if (token != NULL)
  {
    int n = 0;
    if (sscanf(token, "%*[^0-9]%d", &n) == 1 && n > 0 && n <= 30)
    {
      /* Nombre de couleurs explicite */
    }
    else if (token[0] == '#')
    {
      strncpy(colors[num_colors++], token, 15);
      colors[num_colors - 1][15] = '\0';
    }

    while ((token = strtok_r(NULL, ",", &saveptr)) != NULL && num_colors < 30)
    {
      if (token[0] == '#')
      {
        strncpy(colors[num_colors++], token, 15);
        colors[num_colors - 1][15] = '\0';
      }
    }
  }

  if (num_colors == 0)
  {
    num_colors = 1;
    strcpy(colors[0], "#ff0000");
  }

  return plot_colors(colors, num_colors);
}

int renvoie_message(int client_socket_fd, char *data)
{
  int data_size = write(client_socket_fd, (void *)data, strlen(data));
  if (data_size < 0)
  {
    perror("erreur ecriture");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

/**
 * Exercice 6.3 :
 * Traitement des messages au format JSON :
 * - {"code": "message", "valeurs": ["..."]}
 * - {"code": "calcule", "valeurs": ["+", "23", "45"]}
 * - {"code": "couleurs", "valeurs": ["#ff0000", ...]}
 */
static int traiter_message_json(int client_socket_fd, const char *json_str)
{
  char reponse[2048];

  if (strstr(json_str, "\"code\": \"calcule\"") != NULL ||
      strstr(json_str, "\"code\":\"calcule\"") != NULL)
  {
    /* Extraction opérateur et nombres */
    char op = '+';
    float n1 = 0.0f, n2 = 0.0f;
    const char *p_vals = strstr(json_str, "\"valeurs\"");
    if (p_vals)
    {
      /* Recherche de l'opérateur et des valeurs dans ["<op>", "<n1>", "<n2>"] */
      const char *p_bracket = strchr(p_vals, '[');
      if (p_bracket)
      {
        char temp[256];
        strncpy(temp, p_bracket, sizeof(temp) - 1);
        temp[sizeof(temp) - 1] = '\0';

        char op_str[16] = "+", s1[32] = "0", s2[32] = "0";
        if (sscanf(temp, "[\"%15[^\"]\", \"%31[^\"]\", \"%31[^\"]\"]", op_str, s1, s2) >= 3)
        {
          op = op_str[0];
          n1 = (float)atof(s1);
          n2 = (float)atof(s2);
        }
      }
    }

    float res = 0.0f;
    switch (op)
    {
      case '+': res = n1 + n2; break;
      case '-': res = n1 - n2; break;
      case '*': res = n1 * n2; break;
      case '/': res = (n2 != 0.0f) ? (n1 / n2) : 0.0f; break;
      default: res = 0.0f; break;
    }

    printf("Calcul JSON : %g %c %g = %g\n", n1, op, n2, res);
    snprintf(reponse, sizeof(reponse),
             "{\n  \"code\": \"reponse\",\n  \"statut\": \"succes\",\n  \"resultat\": %g\n}\n",
             res);
    return renvoie_message(client_socket_fd, reponse);
  }
  else if (strstr(json_str, "\"code\": \"couleurs\"") != NULL ||
           strstr(json_str, "\"code\":\"couleurs\"") != NULL)
  {
    /* Extraction des codes couleurs #... */
    char colors[32][16];
    int count = 0;
    const char *p = json_str;

    while ((p = strchr(p, '#')) != NULL && count < 30)
    {
      int len = 0;
      while (p[len] != '\"' && p[len] != ',' && p[len] != ']' && p[len] != '\0' && len < 15)
      {
        colors[count][len] = p[len];
        len++;
      }
      colors[count][len] = '\0';
      count++;
      p += len;
    }

    printf("Réception de %d couleurs en format JSON.\n", count);
    if (count > 0)
    {
      plot_colors(colors, count);
    }

    snprintf(reponse, sizeof(reponse),
             "{\n  \"code\": \"reponse\",\n  \"statut\": \"succes\",\n  \"nb_couleurs\": %d\n}\n",
             count);
    return renvoie_message(client_socket_fd, reponse);
  }
  else
  {
    /* Message JSON générique : renvoi écho en JSON */
    snprintf(reponse, sizeof(reponse),
             "{\n  \"code\": \"reponse\",\n  \"statut\": \"succes\",\n  \"message\": \"reçu\"\n}\n");
    return renvoie_message(client_socket_fd, reponse);
  }
}

int recois_envoie_message(int client_socket_fd, char data[2048])
{
  printf("Message reçu: %s\n", data);

  /* Si le message est au format JSON */
  if (data[0] == '{')
  {
    return traiter_message_json(client_socket_fd, data);
  }

  /* Format simple classique */
  char code[16];
  if (sscanf(data, "%15s", code) == 1)
  {
    if (strcmp(code, "message:") == 0)
    {
      return renvoie_message(client_socket_fd, data);
    }
  }

  return plot(data);
}

void gestionnaire_ctrl_c(int signal)
{
  (void)signal; /* Évite l'avertissement unused-parameter */
  printf("\nSignal Ctrl+C capturé. Sortie du programme.\n");
  if (socketfd != -1)
  {
    close(socketfd);
  }
  exit(0);
}

int main(void)
{
  int bind_status;
  struct sockaddr_in server_addr;

  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("Impossible d'ouvrir la socket");
    return -1;
  }

  int option = 1;
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  bind_status = bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (bind_status < 0)
  {
    perror("bind");
    return EXIT_FAILURE;
  }

  signal(SIGINT, gestionnaire_ctrl_c);
  listen(socketfd, 10);

  printf("Serveur en attente de connexions (port %d)...\n", PORT);

  while (1)
  {
    struct sockaddr_in client_addr;
    char data[2048];
    unsigned int client_addr_len = sizeof(client_addr);

    int client_socket_fd = accept(socketfd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket_fd < 0)
    {
      perror("accept");
      continue;
    }

    memset(data, 0, sizeof(data));
    int data_size = read(client_socket_fd, (void *)data, sizeof(data) - 1);

    if (data_size > 0)
    {
      data[data_size] = '\0';
      recois_envoie_message(client_socket_fd, data);
    }

    close(client_socket_fd);
  }

  return 0;
}
