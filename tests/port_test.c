/*
** EPITECH PROJECT, 2022
** Boostrap
** File description:
** step1
*/

#include <sys/types.h>
#include <sys/socket_t.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#define INVALID_SOCKET -1
#define socket_t_ERROR -1
#define CLOSECOKET(s) close(s)
typedef int socket_t;


typedef struct sockaddr_in sockaddr_in_t;
typedef struct sockaddr sockaddr_t;

typedef struct connexion_s {
    socket_t my_socket_t;
    sockaddr_in_t interface;
} connexion_t;

typedef struct node_s {
    connexion_t **data;
    size_t size;
} node_t;

node_t *init_head(void)
{
    node_t *new_node = malloc(sizeof(node_t) * 1);

    if (new_node == NULL)
        return NULL;
    new_node->data = NULL;
    new_node->size = 0;
    return new_node;
}

void add_in_head(node_t *head, connexion_t *connexion_to_add)
{
    head->data = reallocarray(head->data, head->size + 1, sizeof(connexion_t *));
    head->data[head->size] = connexion_to_add;
    head->size += 1;
}

socket_t create_socket(void)
{
    socket_t new_socket = socket_t(AF_INET, SOCK_STREAM, 0);

    if (new_socket == INVALID_SOCKET) {
        fprintf(stderr, "socket_t creation have Failed.\n");
        return INVALID_SOCKET;
    }
    return new_socket_t;
}

void close_socket_t(socket_t closing_sock)
{
    CLOSECOKET(closing_sock);
}

sockaddr_in_t create_interface(int port)
{
    sockaddr_in_t interface;

    interface.sin_addr.s_addr = htonl(INADDR_ANY);
    interface.sin_family = AF_INET;
    interface.sin_port = htons(port);
    return interface;
}

connexion_t *create_host_connexion(int port)
{
    connexion_t *new_connexion = malloc(sizeof(connexion_t));

    new_connexion->my_socket = create_socket();
    new_connexion->interface = create_interface(port);
    return new_connexion;
}

void delete_connexion(connexion_t *host_server)
{
    close_socket_t(host_server->my_socket);
    free(host_server);
}

int binding_interface(socket_t my_socket_t, sockaddr_in_t *interface)
{
    if (bind(my_socket_t, (sockaddr_t *)interface, sizeof *interface) == socket_t_ERROR) {
        fprintf(stderr, "Bind have Failed.\n");
        return socket_t_ERROR;
    }
    return 0;
}

int set_queue_limit(socket_t my_socket_t, int limit)
{
    if (listen(my_socket_t, limit) == socket_t_ERROR) {
        fprintf(stderr, "Listen have Failed.\n");
        return socket_t_ERROR;
    }
    return 0;
}

int write_to_client(socket_t client_socket_t, const char *message)
{
    if (write(client_socket_t, message, strlen(message)) == socket_t_ERROR) {
        fprintf(stderr, "Write have Failed.\n");
        return socket_t_ERROR;
    }
    return 0;
}

connexion_t *create_client_connexion(connexion_t *host_connexion)
{
    connexion_t *new_connexion = malloc(sizeof(connexion_t));
    int size = sizeof new_connexion->interface;

    new_connexion->my_socket = accept(host_connexion->my_socket, (sockaddr_t *)&(new_connexion->interface), &size);
    return new_connexion;
}

int server_connexion(connexion_t *host_connexion, node_t *head)
{
    connexion_t *client_connexion = create_client_connexion(host_connexion);

    if (client_connexion->my_socket == INVALID_SOCKET) {
        fprintf(stderr, "Accept have Failed.\n");
        return socket_t_ERROR;
    }
    add_in_head(head, client_connexion);
    printf("CONNECTED.\n");
    fflush(NULL);
    //delete_connexion(client_connexion);
    return 0;
}

int server_loop(connexion_t *host_connexion, node_t *head, fd_set *readfs, fd_set *writefs)
{
    if (head->size == 0 && server_connexion(host_connexion, head))
        return socket_t_ERROR;

    for (int i = 0; i < head->size; i++) {
            char *message = malloc(sizeof(char) * 200000000);
            int message_size = 0;

            if ((message_size = read(head->data[i]->my_socket, message, 190000000)) == INVALID_SOCKET) {
                fprintf(stderr, "Read have failed.\n");
                return socket_t_ERROR;
            }
            message[message_size] = '\0';
            if (write_to_client(head->data[i]->my_socket, message))
                return socket_t_ERROR;
            printf("%s\n", message);
    }
    return 0;
}

int server(int port)
{
    connexion_t *host_connexion = create_host_connexion(port);
    node_t *head = init_head();
    fd_set readfs;
    fd_set writefs;

    if (host_connexion->my_socket == INVALID_SOCKET)
        return INVALID_SOCKET;
    if (binding_interface(host_connexion->my_socket, &(host_connexion->interface)))
        return socket_t_ERROR;
    if (set_queue_limit(host_connexion->my_socket, 5))
        return socket_t_ERROR;
    while (1) {
        if (server_loop(host_connexion, head, &readfs, &writefs))
            return socket_t_ERROR;
    }
    delete_connexion(host_connexion);
}

int main(int ac, char **av)
{
    int return_value = server(atoi(av[1]));

    if (return_value == -1)
        return 84;
}


/// FAIRE UNE LISTE CHAINE DE CONNEXION_T -> IMPLEMENTER SELECT https://broux.developpez.com/articles/c/socket_ts/