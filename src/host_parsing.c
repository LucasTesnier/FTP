/*
** EPITECH PROJECT, 2022
** FTP
** File description:
** host_parsing
*/

#include "host_parsing.h"
#include "macro.h"
#include "ftp_command.h"
#include <string.h>
#include <stdio.h>

/**
*@brief Get the line from host and port object
*
*@param host
*@param port
*@return char*
*/
char *get_line_from_host_and_port(char *host, int port)
{
    char *line = malloc(sizeof(char) * (strlen(host) + 10));
    int first = port / 256;
    int second = port % 256;

    if (line == NULL)
        return INVALID_HOST;
    sprintf(line, "%s,%i,%i", host, first, second);
    for (int i = 0; i < strlen(line); i++)
        if (line[i] == '.')
            line[i] = ',';
    return line;
}

/**
*@brief Get the port from line object
*
*@param line
*@param port
*@param pos
*@return int
*/
int get_port_from_line(char *line, int *port, int pos)
{
    char *endPtr = NULL;
    int first = strtol(line + pos + 1, &endPtr, 10);
    int second = 0;

    if (line == endPtr)
        return INVALID_LINE;
    line = endPtr + 1;
    second = strtol(line, &endPtr, 10);
    if (line == endPtr)
        return INVALID_LINE;
    *port = 256 * first + second;
    return SUCCESS;
}

/**
*@brief Get the host and port from line object
*
*@param line
*@param host
*@param port
*@return int
*/
int get_host_and_port_from_line(char *line, char *host, int *port)
{
    int count = 0;
    int pos = 0;

    for (int i = 0; i < strlen(line); i++) {
        if (count == 3)
            pos = i;
        if (line[i] == ',') {
            line[i] = '.';
            count++;
        }
    }
    if (count != 5)
        return INVALID_LINE;
    host[0] = '\0';
    strncat(host, line, pos);
    if (get_port_from_line(line, port, pos))
        return INVALID_LINE;
    return SUCCESS;
}

void fill_readfs_select(data_t *head, fd_set *readfs)
{
    for (int i = 0; i < head->size; i++)
        if (head->data[i]->is_active)
            FD_SET(head->data[i]->my_socket, readfs);
}

char *setup_pasv_connection(data_t *head, connexion_t *server,
connexion_t *client)
{
    int port = htons(client->interface.sin_port) * 10;
    sockaddr_in_t *temp = NULL;

    client->d_trans.my_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client->d_trans.my_socket == FTP_ERROR)
        return NULL;
    client->d_trans.interface.sin_port = htons(port);
    temp = &(client->d_trans.interface);
    if (bind(client->d_trans.my_socket, (sockaddr_t *)temp, sizeof *temp) ==
    INVALID_INTERFACE) {
        write_to_client(head, client, "550 Socket bind.\n");
        return NULL;
    }
    client->d_trans.is_active = true;
    return get_line_from_host_and_port("127.0.0.1", port);
}