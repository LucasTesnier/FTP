/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ftp_complex_command
*/

#include "ftp_complex_command.h"
#include "ftp_command.h"
#include "macro.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int command_pwd(data_t *head, connexion_t *server, connexion_t *client,
char *arg)
{
    if (client->is_auth != CONNECTED) {
        if (write_to_client(head, client,
            "532 Need account for execute this command.\n") == FTP_ERROR)
            return FTP_ERROR;
        return FUNCTION_SUCCESS;
    }
    if (write_to_client(head, client, "257 \"") == FTP_ERROR)
        return FTP_ERROR;
    if (write_to_client(head, client, client->current_directory) == FTP_ERROR)
        return FTP_ERROR;
    if (write_to_client(head, client, "\" PWD.\n") == FTP_ERROR)
        return FTP_ERROR;
    return FUNCTION_SUCCESS;
}