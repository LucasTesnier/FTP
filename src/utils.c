/*
** EPITECH PROJECT, 2022
** Project
** File description:
** utils
*/

#include "utils.h"
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
