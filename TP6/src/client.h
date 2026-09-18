/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef __CLIENT_H__
#define __CLIENT_H__

#define PORT 8089

/* Fonction d'envoi et de réception de messages */
int envoie_recois_message(int socketfd);

/* Envoi des couleurs extraites d'une image BMP */
int envoie_couleurs(int socketfd, char *pathname, int nb_couleurs);

/* Analyse de l'image et formatage des couleurs */
void analyse(char *pathname, char *data, int max_couleurs);

#endif
