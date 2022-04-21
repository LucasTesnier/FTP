/*
** EPITECH PROJECT, 2022
** FTP
** File description:
** ftp_file_command
*/

#include "ftp_file_command.h"
#include "ftp_complex_command.h"
#include "ftp_command.h"
#include "ftp_data_command.h"
#include "macro.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void send_file_with_data(data_t *head, connexion_t *server,
connexion_t *client, char *path)
{
    char *message = NULL;
    int pid = fork();

    if (pid == 0) {
        message = get_file_content(path);
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

int command_retr(data_t *head, connexion_t *server, connexion_t *client,
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
    if (is_a_file(path, head, client))
        send_file_with_data(head, server, client, path);
    free(path);
    return FUNCTION_SUCCESS;
}

void get_file_with_data(data_t *head, connexion_t *server, connexion_t *client,
char *path)
{
    int pid = fork();
    char *content = NULL;
    FILE *fptr = NULL;

    if (pid == 0) {
        write_to_client(head, client, "150 File status okay.\n");
        content = get_file_from_data(client, head);
        if (content != NULL && (fptr = fopen(path, "w")) != NULL) {
            fprintf(fptr, "%s", content);
            fclose(fptr);
            write_to_client(head, client, "226 Closing data connection.\n");
        } else
            write_to_client(head, client, "550 Cannot create file.\n");
        CLOSECOKET(client->d_trans.my_socket);
        free(content);
        exit(0);
    }
    client->d_trans.is_active = false;
}

int command_stor(data_t *head, connexion_t *server, connexion_t *client,
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
    get_file_with_data(head, server, client, path);
    free(path);
    return FUNCTION_SUCCESS;
}