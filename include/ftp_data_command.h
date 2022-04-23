/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ftp_data_command
*/

#ifndef FTP_DATA_COMMAND_H_
    #define FTP_DATA_COMMAND_H_

    #include "data_gestion.h"

int connect_to_host(data_t *head, connexion_t *server, connexion_t *client,
char *arg);
int command_port(data_t *head, connexion_t *server, connexion_t *client,
char *arg);
char *get_file_content(char *path);
char *get_file_from_data(connexion_t *client, data_t *head);
int command_pasv(data_t *head, connexion_t *server, connexion_t *client,
char *arg);

#endif /* !FTP_DATA_COMMAND_H_ */
