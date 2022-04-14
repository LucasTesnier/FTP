/*
** EPITECH PROJECT, 2022
** Project
** File description:
** init_ftp
*/

#include "macro.h"
#include "init_ftp.h"
#include "socket_function.h"
#include "ftp_command.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include <signal.h>

static volatile int running = 1;

void init_handler(int dummy)
{
    running = 0;
}

int argument_gestion(int ac, char **av, data_t *head)
{
    char *endPtr = NULL;

    if (ac == 2 && strcmp(av[1], "-h") == 0) {
        display_help(head);
        return ARGUMENT_ERROR;
    }
    if (ac != 3) {
        display_error("Invalid number of arguments.", head);
        return ARGUMENT_ERROR;
    }
    head->home_path = av[2];
    head->port = strtol(av[1], &endPtr, 10);
    if (endPtr == av[1]) {
        display_error("Invalid port. Number only.", head);
        return ARGUMENT_ERROR;
    }
    return FUNCTION_SUCCESS;
}

int readfs_traitment(connexion_t *server, data_t *head, fd_set *readfs)
{
    int return_value = FUNCTION_SUCCESS;

    if (FD_ISSET(server->my_socket, readfs) &&
        server_connexion(server, head) < 0)
        return SERVER_ERROR;
    for (int i = 0; i < head->size; i++) {
        if (head->data[i]->is_active &&
            FD_ISSET(head->data[i]->my_socket, readfs))
            return_value = command_traitment(server, head->data[i], head);
        if (return_value == SERVER_ERROR)
            return SERVER_ERROR;
    }
    return FUNCTION_SUCCESS;
}

int server_loop(connexion_t *server, data_t *head)
{
    fd_set readfs;
    SOCKET max = 0;

    while (running) {
        FD_ZERO(&readfs);
        FD_SET(server->my_socket, &readfs);
        for (int i = 0; i < head->size; i++)
            if (head->data[i]->is_active)
                FD_SET(head->data[i]->my_socket, &readfs);
        max = ((head->size > 0) ? head->data[head->size - 1]->my_socket : \
        server->my_socket);
        if (select(max + 1, &readfs, NULL, NULL, NULL) < 0 && running == 1) {
            display_error("Select have failed.", head);
            return SERVER_ERROR;
        }
        if (running == 0)
            return FUNCTION_SUCCESS;
        if (readfs_traitment(server, head, &readfs))
            return SERVER_ERROR;
    }
    return FUNCTION_SUCCESS;
}

int init_ftp(int ac, char **av)
{
    data_t *head = init_data();
    connexion_t *server = NULL;

    if (head == NULL)
        return FTP_ERROR;
    if (argument_gestion(ac, av, head) == ARGUMENT_ERROR)
        return ARGUMENT_ERROR;
    if ((server = server_init(head)) == NULL)
        return SERVER_ERROR;
    signal(SIGINT, init_handler);
    if (server_loop(server, head) == SERVER_ERROR)
        return SERVER_ERROR;
    destroy_server(server);
    destroy_data(head);
    return PROGRAM_SUCCESS;
}
