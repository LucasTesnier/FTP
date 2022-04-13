/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ftp_command
*/

#ifndef FTP_COMMAND_H_
    #define FTP_COMMAND_H_

    #include "data_gestion.h"

typedef struct command_s {
    char *name;
    char *arg;
    int (*func)(data_t *, connexion_t *, connexion_t *, char *);
} command_t;

int command_traitment(connexion_t *server, connexion_t *client, data_t *head);
char *read_command(connexion_t *client, data_t *head);
int write_to_client(data_t *head, connexion_t *client, char *message);
command_t parse_command(char *command);
int find_matching_command(command_t command);

#endif /* !FTP_COMMAND_H_ */
