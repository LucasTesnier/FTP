/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ftp_help_command
*/

#include "ftp_help_command.h"
#include "ftp_command.h"
#include "ftp_complex_command.h"
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

char *read_list_content(FILE *file)
{
    char *buffer = NULL;
    long length = 0;

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = malloc(sizeof(char) * (length + 10000));
    if (buffer == NULL)
        return NULL;
    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    return buffer;
}

char *get_list_content(char *path, char *home)
{
    FILE *file;
    char temp[10000];
    char *message = NULL;

    temp[0] = '\0';
    strcat(temp, "/bin/ls ");
    if (strcmp(path, "")) {
        strcat(temp, path);
    } else
        strcat(temp, home);
    file = popen(temp, "r");
    if (file == NULL)
        return NULL;
    message = read_list_content(file);
    pclose(file);
    return message;
}

void send_list_with_data(data_t *head, connexion_t *server, connexion_t *client,
char *path)
{
    char *message = NULL;
    int pid = fork();

    if (pid == 0) {
        message = get_list_content(path, client->current_directory);
        write_to_client(head, client, "150 File status okay.\n");
        if (write(client->d_trans.my_socket, message,
        strlen(message)) == FTP_ERROR) {
            write_to_client(head, client, "550 Write have failed.\n");
            return;
        }
        write_to_client(head, client, "226 Closing data connection.\n");
        CLOSECOKET(client->d_trans.my_socket);
        free(message);
        exit(0);
    }
    client->d_trans.is_active = false;
}

int command_list(data_t *head, connexion_t *server, connexion_t *client,
char *arg)
{
    char *path = NULL;

    if (client->is_auth != CONNECTED) {
        if (write_to_client(head, client,
        "530 Need account for execute this command.\n") == FTP_ERROR)
            return FTP_ERROR;
        return FUNCTION_SUCCESS;
    }
    if (!client->d_trans.is_active) {
        write_to_client(head, client,
        "550 Need Data socket before execute command.\n");
        return FUNCTION_SUCCESS;
    }
    if ((path = command_cwd_new_path(head, server, client, arg)) == NULL)
        return FTP_ERROR;
    send_list_with_data(head, server, client, path);
    if (strcmp(path, ""))
        free(path);
    return FUNCTION_SUCCESS;
}