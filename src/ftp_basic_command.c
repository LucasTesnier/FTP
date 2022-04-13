/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ftp_basic_command
*/

#include "ftp_basic_command.h"
#include "ftp_command.h"
#include "macro.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int command_quit(data_t *head, connexion_t *server, connexion_t *client,
char *arg)
{
    (void) server;
    (void) arg;
    if (write_to_client(head, client,
    "221 Service closing control connection.\n") == FTP_ERROR) {
        return FTP_ERROR;
    }
    closesocket(client->my_socket);
    client->is_active = false;
    return FUNCTION_SUCCESS;
}

int command_invalid(data_t *head, connexion_t *server, connexion_t *client)
{
    if (write_to_client(head, client,
    "500 Syntax error, command unrecognized.\n") == FTP_ERROR) {
        return FTP_ERROR;
    }
    (void) server;
    return FUNCTION_SUCCESS;
}