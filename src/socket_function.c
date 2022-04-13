/*
** EPITECH PROJECT, 2022
** Project
** File description:
** socket_function
*/

#include "socket_function.h"
#include "macro.h"
#include "utils.h"
#include <stdlib.h>

SOCKET create_socket(data_t *head)
{
    SOCKET new_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (new_socket == INVALID_SOCKET) {
        display_error("Socket creation have Failed.\n", head);
        return INVALID_SOCKET;
    }
    return new_socket;
}

sockaddr_in_t create_interface(data_t *head)
{
    sockaddr_in_t interface;

    interface.sin_addr.s_addr = htonl(INADDR_ANY);
    interface.sin_family = AF_INET;
    interface.sin_port = htons(head->port);
    return interface;
}

int binding_interface(connexion_t *server, data_t *head)
{
    sockaddr_in_t *temp = &(server->interface);

    if (bind(server->my_socket, (sockaddr_t *)temp, sizeof *temp) == INVALID_INTERFACE) {
        display_error("Bind have failed. Port already taken.", head);
        return INVALID_INTERFACE;
    }
    return FUNCTION_SUCCESS;
}

int set_queue_limit(connexion_t *server, data_t *head)
{
    if (listen(server->my_socket, 5) == INVALID_SOCKET) {
        display_error("Listen have Failed.", head);
        closesocket(server->my_socket);
        free(server);
        return INVALID_SOCKET;
    }
    return FUNCTION_SUCCESS;
}