/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ftp_command
*/

#ifndef FTP_COMMAND_H_
    #define FTP_COMMAND_H_

    #include "data_gestion.h"

int command_traitment(connexion_t *server, connexion_t *client, data_t *head);
char *read_command(connexion_t *client, data_t *head);

#endif /* !FTP_COMMAND_H_ */
