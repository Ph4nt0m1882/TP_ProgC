/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef __SERVER_H__
#define __SERVER_H__

#define PORT 8089

#define SVG_FILE_PATH "pie_chart.svg"

/* Renvoie un message au client */
int renvoie_message(int client_socket_fd, char *data);

/* Lit et traite les messages (format JSON ou simple) envoyés par le client */
int recois_envoie_message(int client_socket_fd, char data[2048]);

/* Génère le diagramme circulaire SVG à partir d'un ensemble de couleurs */
int plot(char *data);
int plot_colors(char colors[][16], int num_colors);

#endif
