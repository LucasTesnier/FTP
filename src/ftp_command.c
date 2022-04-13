/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ftp_command
*/

#include "ftp_command.h"
#include "macro.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

char *read_command(connexion_t *client, data_t *head)
{
    char *message = malloc(sizeof(char) * 4086);
    int message_size = 0;

    if ((message_size = read(client->my_socket, message, 4084))
    == INVALID_SOCKET) {
        display_error("Read have failed.", head);
        return NULL;
    }
    message[message_size -1] = '\0';
    return message;
}

int command_traitment(connexion_t *server, connexion_t *client, data_t *head)
{
    char *command = read_command(client, head);

    if (command == NULL)
        return FTP_ERROR;
    fprintf(stdout, "%s\n", command);
    free(command);
    return FUNCTION_SUCCESS;
}