/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ftp_complex_command
*/

#ifndef FTP_COMPLEX_COMMAND_H_
    #define FTP_COMPLEX_COMMAND_H_

    #include "data_gestion.h"

int command_pwd(data_t *head, connexion_t *server, connexion_t *client,
char *arg);
int command_cwd(data_t *head, connexion_t *server, connexion_t *client,
char *arg);
int command_cdup(data_t *head, connexion_t *server, connexion_t *client,
char *arg);
int command_dele(data_t *head, connexion_t *server, connexion_t *client,
char *arg);

#endif /* !FTP_COMPLEX_COMMAND_H_ */
