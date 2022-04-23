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

/**
*@brief do the QUIT command
*
*@param head
*@param server
*@param client
*@param arg
*@return int
*/
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
    if (client->d_trans.is_active)
        CLOSECOKET(client->d_trans.my_socket);
    CLOSECOKET(client->my_socket);
    free(client->current_directory);
    client->is_active = false;
    return FUNCTION_SUCCESS;
}

/**
*@brief do the USER command
*
*@param head
*@param server
*@param client
*@param arg
*@return int
*/
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
            "331 Invalid user name.\n") == FTP_ERROR)
            return FTP_ERROR;
    }
    return FUNCTION_SUCCESS;
}

/**
*@brief do the PASS command
*
*@param head
*@param server
*@param client
*@param arg
*@return int
*/
int command_pass(data_t *head, connexion_t *server, connexion_t *client,
char *arg)
{
    if (client->is_auth != USER) {
        if (write_to_client(head, client,
            "530 Need account for login.\n") == FTP_ERROR)
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

/**
*@brief do the NOOP command
*
*@param head
*@param server
*@param client
*@param arg
*@return int
*/
int command_noop(data_t *head, connexion_t *server, connexion_t *client,
char *arg)
{
    if (client->is_auth != CONNECTED) {
        if (write_to_client(head, client,
            "530 Need account for execute this command.\n") == FTP_ERROR)
            return FTP_ERROR;
        return FUNCTION_SUCCESS;
    }
    if (write_to_client(head, client, "200 Command okay.\n") == FTP_ERROR)
        return FTP_ERROR;
    return FUNCTION_SUCCESS;
}

/**
*@brief In case of invalid / unknown command
*
*@param head
*@param server
*@param client
*@return int
*/
int command_invalid(data_t *head, connexion_t *server, connexion_t *client)
{
    if (write_to_client(head, client,
    "500 Syntax error, command unrecognized.\n") == FTP_ERROR) {
        return FTP_ERROR;
    }
    (void) server;
    return FUNCTION_SUCCESS;
}
