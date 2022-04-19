/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ftp_data_command
*/

#include "ftp_data_command.h"
#include "ftp_command.h"
#include "macro.h"
#include "socket_function.h"
#include "host_parsing.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>

int connect_to_host(data_t *head, connexion_t *server, connexion_t *client,
char *arg)
{
    char *host = malloc(sizeof(char) * 40);
    int port = 0;
    struct hostent *hostinfo = NULL;

    if (get_host_and_port_from_line(arg, host, &port))
        return FTP_ERROR;
    if ((hostinfo = gethostbyname(host)) == NULL)
        return FTP_ERROR;
    client->d_trans.interface.sin_addr.s_addr = *(in_addr_t *)hostinfo->h_addr;
    client->d_trans.interface.sin_family = AF_INET;
    client->d_trans.interface.sin_port = htons(port);
    if (connect(client->d_trans.my_socket,
        (sockaddr_t *)(&client->d_trans.interface),
        sizeof(sockaddr_t)) == FTP_ERROR)
        return FTP_ERROR;
    client->d_trans.is_active = true;
    free(host);
    return FUNCTION_SUCCESS;
}

int command_port(data_t *head, connexion_t *server, connexion_t *client,
char *arg)
{
    if (client->is_auth != CONNECTED) {
        if (write_to_client(head, client,
            "530 Need account for execute this command.\n") == FTP_ERROR)
            return FTP_ERROR;
        return FUNCTION_SUCCESS;
    }
    if (client->d_trans.is_active == true) {
        if (write_to_client(head, client, "550 Socket bind.\n") == FTP_ERROR)
            return FTP_ERROR;
        return FUNCTION_SUCCESS;
    }
    if ((client->d_trans.my_socket = create_socket(head)) == FTP_ERROR)
        return FTP_ERROR;
    if (connect_to_host(head, server, client, arg) == FTP_ERROR) {
        if (write_to_client(head, client, "550 Bind error.\n") == FTP_ERROR)
            return FTP_ERROR;
        return FUNCTION_SUCCESS;
    }
    write_to_client(head, client, "200 Command okay.\n");
    return FUNCTION_SUCCESS;
}