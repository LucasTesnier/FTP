/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ftp_help_command
*/

#ifndef FTP_HELP_COMMAND_H_
    #define FTP_HELP_COMMAND_H_

    #include "data_gestion.h"

int command_help(data_t *head, connexion_t *server, connexion_t *client,
char *arg);
int command_list(data_t *head, connexion_t *server, connexion_t *client,
char *arg);

#endif /* !FTP_HELP_COMMAND_H_ */
