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
            "530 Need account for execute this command.\n") == FTP_ERROR)
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

char *command_cwd_new_path(data_t *head, connexion_t *server,
connexion_t *client, char *arg)
{
    char *path = strdup(client->current_directory);

    if (path == NULL)
        return NULL;
    if (arg[0] != '/') {
        path = realloc(path, strlen(arg) + strlen(path) + 2);
        if (path == NULL)
            return NULL;
        path[strlen(client->current_directory)] = '/';
        path[strlen(client->current_directory) + 1] = '\0';
        strcat(path, arg);
    } else {
        free(path);
        path = strdup(arg);
        if (path == NULL)
            return NULL;
    }
    return path;
}

int command_cwd(data_t *head, connexion_t *server, connexion_t *client,
char *arg)
{
    char *path = NULL;

    if (client->is_auth != CONNECTED) {
        if (write_to_client(head, client,
            "530 Need account for execute this command.\n") == FTP_ERROR)
            return FTP_ERROR;
        return FUNCTION_SUCCESS;
    }
    if ((path = command_cwd_new_path(head, server, client, arg)) == NULL)
        return FTP_ERROR;
    if (is_a_directory(path, true, head, client) == 1) {
        free(client->current_directory);
        client->current_directory = path;
        if (write_to_client(head, client,
            "250 Requested file action okay, completed.\n") == FTP_ERROR)
            return FTP_ERROR;
    }
    return FUNCTION_SUCCESS;
}

int command_cdup(data_t *head, connexion_t *server, connexion_t *client,
char *arg)
{
    char *new_path = NULL;

    if (client->is_auth != CONNECTED) {
        if (write_to_client(head, client,
            "530 Need account for execute this command.\n") == FTP_ERROR)
            return FTP_ERROR;
        return FUNCTION_SUCCESS;
    }
    if ((new_path = go_back_path(client->current_directory,
        head, client)) == NULL)
        return FTP_ERROR;
    if (is_a_directory(new_path, true, head, client) == 1) {
        free(client->current_directory);
        client->current_directory = new_path;
        if (write_to_client(head, client,
            "200 Command okay.\n") == FTP_ERROR)
            return FTP_ERROR;
    }
    return FUNCTION_SUCCESS;
}

int command_dele(data_t *head, connexion_t *server, connexion_t *client,
char *arg)
{
    char *path = NULL;

    if (client->is_auth != CONNECTED) {
        if (write_to_client(head, client,
            "530 Need account for execute this command.\n") == FTP_ERROR)
            return FTP_ERROR;
        return FUNCTION_SUCCESS;
    }
    if ((path = command_cwd_new_path(head, server, client, arg)) == NULL)
        return FTP_ERROR;
    if (remove(path)) {
        if (write_to_client(head, client,
            "550 Can't remove file.\n") == FTP_ERROR)
            return FTP_ERROR;
    } else {
        if (write_to_client(head, client,
            "250 Requested file action okay, completed.\n") == FTP_ERROR)
            return FTP_ERROR;
    }
    free(path);
    return FUNCTION_SUCCESS;
}