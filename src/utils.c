/*
** EPITECH PROJECT, 2022
** Project
** File description:
** utils
*/

#include "utils.h"
#include "macro.h"
#include "ftp_command.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
*@brief display --help
*
*@param head
*/
void display_help(data_t *head)
{
    printf("My FTP Usage\n");
    destroy_data(head);
}

/**
*@brief display an error message and destroy the head
*
*@param str
*@param head
*/
void display_error(char *str, data_t *head)
{
    fprintf(stderr, "%s\n", str);
    destroy_data(head);
}

int is_a_directory(char *path, bool blocking, data_t *head,
connexion_t *client)
{
    struct stat sb;

    if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
        return A_DIRECTORY;
    } else {
        if (blocking) {
            if (write_to_client(head, client,
            "550 File is not a directory.\n") == FTP_ERROR)
            return FTP_ERROR;
        }
        return NOT_A_DIRECTORY;
    }
}

char *go_back_path(char *path, data_t *head, connexion_t *client)
{
    char *new_path = strdup(path);
    int count = 0;
    int coun = 0;

    for (int i = 0; i < strlen(new_path); i++)
        if (new_path[i] == '/')
            count++;
    if (count == 0 || count == 1) {
        new_path[0] = '/';
        new_path[1] = '\0';
        return new_path;
    }
    for (int i = 0; i < strlen(new_path); i++) {
        if (new_path[i] == '/')
            coun++;
        if (coun == count) {
            new_path[i] = '\0';
            break;
        }
    }
    return new_path;
}