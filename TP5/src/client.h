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

/* Exercice 5.5 : Fonction d'envoi d'opérations de calcul au serveur */
int envoie_operateur_numeros(int socketfd, char op, float num1, float num2);

/* Exercice 5.6 : Calculs sur les notes des étudiants */
void calculer_notes_etudiants(int socketfd);

#endif
