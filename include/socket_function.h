/*
** EPITECH PROJECT, 2022
** Project
** File description:
** socket_t_function
*/

#ifndef socket_t_FUNCTION_H_
    #define socket_t_FUNCTION_H_

    #include "data_gestion.h"

socket_t create_socket(data_t *head);
sockaddr_in_t create_interface(data_t *head);
int binding_interface(connexion_t *server, data_t *head);
int set_queue_limit(connexion_t *server, data_t *head);
int server_connexion(connexion_t *server, data_t *head);

#endif /* !socket_t_FUNCTION_H_ */
