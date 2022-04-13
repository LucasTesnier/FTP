/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ftp_t_gestion
*/

#include "data_gestion.h"
#include "socket_function.h"
#include "macro.h"
#include <stdlib.h>

data_t *init_data(void)
{
    data_t *head = malloc(sizeof(data_t) * 1);

    if (head == NULL)
        return NULL;
    head->data = NULL;
    head->size = 0;
    head->port = 0;
    head->home_path = NULL;
    return head;
}

void destroy_data(data_t *head)
{
    for (int i = 0; i < head->size; i++) {
        if (head->data[i]->is_active) {
            closesocket(head->data[i]->my_socket);
            free(head->data[i]);
        }
    }
    free(head);
}

connexion_t *server_init(data_t *head)
{
    connexion_t *server = malloc(sizeof(connexion_t) * 1);

    if (server == NULL) {
        destroy_data(head);
        return NULL;
    }
    server->my_socket = create_socket(head);
    if (server->my_socket == INVALID_SOCKET)
        return NULL;
    server->interface = create_interface(head);
    if (binding_interface(server, head) == INVALID_INTERFACE) {
        closesocket(server->my_socket);
        free(server);
        return NULL;
    }
    server->is_active = true;
    return server;
}

void destroy_server(connexion_t *server)
{
    closesocket(server->my_socket);
    free(server);
}