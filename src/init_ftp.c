/*
** EPITECH PROJECT, 2022
** Project
** File description:
** init_ftp
*/

#include "macro.h"
#include "init_ftp.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void display_help(data_t *head)
{
    printf("My FTP Usage\n");
    destroy_data(head);
}

void display_error(char *str, data_t *head)
{
    fprintf(stderr, "%s\n", str);
    destroy_data(head);
}

int argument_gestion(int ac, char **av, data_t *head)
{
    char *endPtr = NULL;

    if (ac == 2 && strcmp(av[1], "-h") == 0) {
        display_help(head);
        return ARGUMENT_ERROR;
    }
    if (ac != 3) {
        display_error("Invalid number of arguments.", head);
        return ARGUMENT_ERROR;
    }
    head->home_path = av[2];
    head->port = strtol(av[1], &endPtr, 10);
    if (endPtr == av[1]) {
        display_error("Invalid port. Number only.", head);
        return ARGUMENT_ERROR;
    }
    return FUNCTION_SUCCESS;
}

int init_ftp(int ac, char **av)
{
    data_t *head = init_data();

    if (head == NULL)
        return FTP_ERROR;
    if (argument_gestion(ac, av, head) == ARGUMENT_ERROR)
        return ARGUMENT_ERROR;
    destroy_data(head);
    return PROGRAM_SUCCESS;
}