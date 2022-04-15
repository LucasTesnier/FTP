/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ftp_data_command
*/

#include "ftp_data_command.h"
#include "ftp_command.h"
#include "macro.h"
#include "socket_function.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>

int command_port(data_t *head, connexion_t *server, connexion_t *client,
char *arg)
{
    (void) head;
    (void) server;
    (void) client;
    (void) arg;
    return FUNCTION_SUCCESS;
}