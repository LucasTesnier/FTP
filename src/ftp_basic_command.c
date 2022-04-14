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
    char *message = NULL;

    (void) server;
    (void) arg;
    if (client->is_auth == CONNECTED)
        message = "221 Logout. Service closing control connection.\n";
    else
        message = "221 Service closing control connection.\n";
    if (write_to_client(head, client, message) == FTP_ERROR) {
        return FTP_ERROR;
    }
    closesocket(client->my_socket);
    client->is_active = false;
    return FUNCTION_SUCCESS;
}

int command_user(data_t *head, connexion_t *server, connexion_t *client,
char *arg)
{
    if (strcmp(arg, "Anonymous") == 0) {
        if (write_to_client(head, client,
            "331 User name okay, need password.\n") == FTP_ERROR)
            return FTP_ERROR;
        client->is_auth = USER;
    } else {
        if (write_to_client(head, client,
            "430 Invalid user name.\n") == FTP_ERROR)
            return FTP_ERROR;
    }
    return FUNCTION_SUCCESS;
}

int command_pass(data_t *head, connexion_t *server, connexion_t *client,
char *arg)
{
    if (client->is_auth != USER) {
        if (write_to_client(head, client,
            "332 Need account for login.\n") == FTP_ERROR)
            return FTP_ERROR;
        return FUNCTION_SUCCESS;
    }
    if (strcmp(arg, "") == 0) {
        if (write_to_client(head, client,
            "230 User logged in, proceed.\n") == FTP_ERROR)
            return FTP_ERROR;
        client->is_auth = CONNECTED;
    } else {
        if (write_to_client(head, client,
            "430 Invalid password.\n") == FTP_ERROR)
            return FTP_ERROR;
    }
    return FUNCTION_SUCCESS;
}

int command_noop(data_t *head, connexion_t *server, connexion_t *client,
char *arg)
{
    if (client->is_auth != CONNECTED) {
        if (write_to_client(head, client,
            "532 Need account for execute this command.\n") == FTP_ERROR)
            return FTP_ERROR;
        return FUNCTION_SUCCESS;
    }
    if (write_to_client(head, client, "200 Command okay.\n") == FTP_ERROR)
        return FTP_ERROR;
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
