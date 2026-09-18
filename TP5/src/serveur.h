/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef __SERVER_H__
#define __SERVER_H__

#define PORT 8089

/* Accepter la nouvelle connexion d'un client et envoyer un message */
int renvoie_message(int client_socket_fd, char *data);

/* Lit et traite les messages reçus */
int recois_envoie_message(int client_socket_fd, char *data);

/* Exercice 5.5 & 5.6 : Reçoit une opération de calcul et renvoie le résultat */
int recois_numeros_calcule(int client_socket_fd, char *data);

#endif
