/*
** EPITECH PROJECT, 2022
** Project
** File description:
** socket_function
*/

#ifndef SOCKET_FUNCTION_H_
    #define SOCKET_FUNCTION_H_

    #include "data_gestion.h"

SOCKET create_socket(data_t *head);
sockaddr_in_t create_interface(data_t *head);
int binding_interface(connexion_t *server, data_t *head);
int set_queue_limit(connexion_t *server, data_t *head);
int server_connexion(connexion_t *server, data_t *head);

#endif /* !SOCKET_FUNCTION_H_ */
