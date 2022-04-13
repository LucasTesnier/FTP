/*
** EPITECH PROJECT, 2022
** Project
** File description:
** init_ftp
*/

#include "macro.h"
#include "init_ftp.h"
#include <stdlib.h>

int argument_gestion(int ac, char **av, data_t *head)
{
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