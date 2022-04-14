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

/**
*@brief init the data structure
*
*@return data_t*
*/
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

/**
*@brief destroy the data structure
*
*@param head
*/
void destroy_data(data_t *head)
{
    for (int i = 0; i < head->size; i++) {
        if (head->data[i]->is_active) {
            closesocket(head->data[i]->my_socket);
        }
        free(head->data[i]);
    }
    free(head->data);
    free(head);
}

/**
*@brief init the server connexion
*
*@param head
*@return connexion_t*
*/
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
    if (set_queue_limit(server, head) == INVALID_INTERFACE)
        return NULL;
    server->is_active = true;
    server->is_auth = OFFLINE;
    return server;
}

/**
*@brief destroy the server connexion
*
*@param server
*/
void destroy_server(connexion_t *server)
{
    closesocket(server->my_socket);
    free(server);
}

/**
*@brief add a connexion into the head
*
*@param head
*@param client
*@return int
*/
int add_in_head(data_t *head, connexion_t *client)
{
    head->data = reallocarray(head->data, head->size + 1,
    sizeof(connexion_t *));
    if (head->data == NULL)
        return FTP_ERROR;
    head->data[head->size] = client;
    head->size += 1;
    return FUNCTION_SUCCESS;
}
