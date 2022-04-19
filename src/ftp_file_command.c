/*
** EPITECH PROJECT, 2022
** FTP
** File description:
** ftp_file_command
*/

#include "ftp_file_command.h"
#include "ftp_complex_command.h"
#include "ftp_command.h"
#include "macro.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *get_file_content(char *path)
{
    char *buffer = NULL;
    long length = 0;
    FILE *file = fopen(path, "rb");

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = malloc(sizeof(char) * (length + 1));
    if (buffer == NULL)
        return NULL;
    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);
    return buffer;
}

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