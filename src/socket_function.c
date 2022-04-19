/*
** EPITECH PROJECT, 2022
** Project
** File description:
** socket_t_function
*/

#include "socket_function.h"
#include "ftp_command.h"
#include "macro.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
*@brief Create a socket_t object
*
*@param head
*@return socket_t
*/
socket_t create_socket_t(data_t *head)
{
    socket_t new_socket_t = socket(AF_INET, SOCK_STREAM, 0);

    if (new_socket_t == INVALID_socket_t) {
        display_error("socket_t creation have Failed.\n", head);
        return INVALID_socket_t;
    }
    return new_socket_t;
}

/**
*@brief Create a interface object
*
*@param head
*@return sockaddr_in_t
*/
sockaddr_in_t create_interface(data_t *head)
{
    sockaddr_in_t interface;

    interface.sin_addr.s_addr = htonl(INADDR_ANY);
    interface.sin_family = AF_INET;
    interface.sin_port = htons(head->port);
    return interface;
}

/**
*@brief bind an interface with is socket_t
*
*@param server
*@param head
*@return int
*/
int binding_interface(connexion_t *server, data_t *head)
{
    sockaddr_in_t *temp = &(server->interface);

    if (bind(server->my_socket_t, (sockaddr_t *)temp, sizeof *temp) ==
    INVALID_INTERFACE) {
        display_error("Bind have failed. Port already taken.", head);
        return INVALID_INTERFACE;
    }
    return FUNCTION_SUCCESS;
}

/**
*@brief Set the queue limit object
*
*@param server
*@param head
*@return int
*/
int set_queue_limit(connexion_t *server, data_t *head)
{
    if (listen(server->my_socket_t, 5) == INVALID_socket_t) {
        display_error("Listen have Failed.", head);
        CLOSE_SOCKET(server->my_socket_t);
        free(server);
        return INVALID_socket_t;
    }
    return FUNCTION_SUCCESS;
}

/**
*@brief Hold the accept of a new client process
*
*@param server
*@param head
*@return int
*/
int server_connexion(connexion_t *server, data_t *head)
{
    connexion_t *client = malloc(sizeof(connexion_t));
    socklen_t size = sizeof client->interface;

    if (client == NULL)
        return SERVER_ERROR;
    client->my_socket_t = accept(server->my_socket_t,
    (sockaddr_t *)&(client->interface), &size);
    if (client->my_socket_t == INVALID_socket_t) {
        display_error("Accept have Failed.", head);
        return SERVER_ERROR;
    }
    client->is_active = true;
    client->is_auth = OFFLINE;
    client->current_directory = strdup(head->home_path);
    client->d_trans = (data_transfert_t) {0, create_interface(head), false};
    write_to_client(head, client, "220 Service ready for new user.\n");
    if (add_in_head(head, client))
        return SERVER_ERROR;
    return FUNCTION_SUCCESS;
}
