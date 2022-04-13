/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ftp_t_gestion
*/

#include "data_gestion.h"
#include <stdlib.h>

data_t *init_data(void)
{
    data_t *head = malloc(sizeof(data_t) * 1);

    if (head == NULL)
        return NULL;
    head->data = NULL;
    head->size = 0;
    head->port = 0;
    head->home_path = NULL;
    return head;
}

void destroy_data(data_t *head)
{
    for (int i = 0; i < head->size; i++) {
        if (head->data[i]->is_active) {
            closesocket(head->data[i]->my_socket);
            free(head->data[i]);
        }
    }
    free(head);
}