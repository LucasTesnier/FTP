/*
** EPITECH PROJECT, 2022
** FTP
** File description:
** host_parsing
*/

#ifndef HOST_PARSING_H_
    #define HOST_PARSING_H_

    #include <stdlib.h>
    #include "data_gestion.h"

    #define INVALID_HOST NULL
    #define INVALID_LINE -1
    #define SUCCESS 0

char *get_line_from_host_and_port(char *host, int port);
int get_host_and_port_from_line(char *line, char *host, int *port);
int get_port_from_line(char *line, int *port, int pos);
char *setup_pasv_connection(data_t *head, connexion_t *server,
connexion_t *client);
void fill_readfs_select(data_t *head, fd_set *readfs);

#endif /* !HOST_PARSING_H_ */
