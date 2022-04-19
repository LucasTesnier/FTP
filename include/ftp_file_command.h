/*
** EPITECH PROJECT, 2022
** FTP
** File description:
** ftp_file_command
*/

#ifndef FTP_FILE_COMMAND_H_
    #define FTP_FILE_COMMAND_H_

    #include "data_gestion.h"

int command_retr(data_t *head, connexion_t *server, connexion_t *client,
char *arg);

#endif /* !FTP_FILE_COMMAND_H_ */
