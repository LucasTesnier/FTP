/*
** EPITECH PROJECT, 2022
** Project
** File description:
** init_ftp
*/

#include "macro.h"
#include "init_ftp.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include <signal.h>

static volatile int keepRunning = 1;

void initHandler(int dummy)
{
    keepRunning = 0;
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

int server_loop(connexion_t *server, data_t *head)
{
    while(keepRunning) {
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
    signal(SIGINT, initHandler);
    if (server_loop(server, head) == SERVER_ERROR)
        return SERVER_ERROR;
    destroy_server(server);
    destroy_data(head);
    return PROGRAM_SUCCESS;
}