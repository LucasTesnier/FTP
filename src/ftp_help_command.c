/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ftp_help_command
*/

#include "ftp_help_command.h"
#include "ftp_command.h"
#include "macro.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
*@brief do the HELP command
*
*@param head
*@param server
*@param client
*@param arg
*@return int
*/
int command_help(data_t *head, connexion_t *server, connexion_t *client,
char *arg)
{
    if (write_to_client(head, client, "214 Help message.\n") == FTP_ERROR)
        return FTP_ERROR;
    return FUNCTION_SUCCESS;
}