/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ftp_command
*/

#include "ftp_command.h"
#include "macro.h"
#include "ftp_basic_command.h"
#include "ftp_complex_command.h"
#include "ftp_help_command.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int command_number = 9;

static command_t all_command[] = {
    {"QUIT", NULL, &command_quit},
    {"NOOP", NULL, &command_noop},
    {"HELP", NULL, &command_help},
    {"PWD", NULL, &command_pwd},
    {"CDUP", NULL, &command_cdup},
    {"USER", "", &command_user},
    {"PASS", "", &command_pass},
    {"CWD", "", &command_cwd},
    {"DEL", "", &command_del}
};

/**
*@brief write a message to the client socket
*
*@param head
*@param client
*@param message
*@return int
*/
int write_to_client(data_t *head, connexion_t *client, char *message)
{
    if (write(client->my_socket, message, strlen(message)) == FTP_ERROR) {
        display_error("Write have Failed.", head);
        return FTP_ERROR;
    }
    return FUNCTION_SUCCESS;
}

/**
*@brief read a message from the client socket
*
*@param client
*@param head
*@return char*
*/
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

/**
*@brief parse the receive command
*
*@param command
*@return command_t
*/
command_t parse_command(char *command)
{
    command_t actual_command;
    int count = 0;

    actual_command.func = &command_quit;
    actual_command.arg = NULL;
    for (; count < strlen(command); count++)
        if (command[count] == ' ')
            break;
    actual_command.name = command;
    if (count != strlen(command)) {
        actual_command.name[count] = '\0';
        actual_command.arg = command + count + 1;
        actual_command.arg[strlen(actual_command.arg) - 1] = '\0';
    } else {
        actual_command.name[count - 1] = '\0';
    }
    return actual_command;
}

/**
*@brief find the matching command to the user request
*
*@param command
*@return int
*/
int find_matching_command(command_t command)
{
    int count = 0;

    for (; count < command_number; count++)
        if (strcmp(all_command[count].name, command.name) == 0)
            break;
    if (count == command_number)
        return -1;
    if (all_command[count].arg == NULL) {
        if (command.arg == NULL)
            return count;
    }
    if (all_command[count].arg != NULL) {
        if (command.arg != NULL)
            return count;
    }
    return -1;
}

/**
*@brief Hold all the command process
*
*@param server
*@param client
*@param head
*@return int
*/
int command_traitment(connexion_t *server, connexion_t *client, data_t *head)
{
    char *command = read_command(client, head);
    command_t actual;
    int matching = 0;

    if (command == NULL)
        return FTP_ERROR;
    actual = parse_command(command);
    matching = find_matching_command(actual);
    if (matching == -1) {
        if (command_invalid(head, server, client) == FTP_ERROR)
            return FTP_ERROR;
    } else {
        if ((*all_command[matching].func)(head, server,
            client, actual.arg) == FTP_ERROR)
            return FTP_ERROR;
    }
    free(command);
    return FUNCTION_SUCCESS;
}
