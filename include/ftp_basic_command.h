/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ftp_basic_command
*/

#ifndef FTP_BASIC_COMMAND_H_
    #define FTP_BASIC_COMMAND_H_

    #include "data_gestion.h"

int command_quit(data_t *head, connexion_t *server, connexion_t *client,
char *arg);
int command_invalid(data_t *head, connexion_t *server, connexion_t *client);
int command_user(data_t *head, connexion_t *server, connexion_t *client,
char *arg);
int command_pass(data_t *head, connexion_t *server, connexion_t *client,
char *arg);

#endif /* !FTP_BASIC_COMMAND_H_ */
