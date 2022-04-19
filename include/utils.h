/*
** EPITECH PROJECT, 2022
** Project
** File description:
** utils
*/

#ifndef UTILS_H_
    #define UTILS_H_

    #include "data_gestion.h"

void display_help(data_t *head);
void display_error(char *str, data_t *head);
int is_a_directory(char *path, bool blocking, data_t *head,
connexion_t *client);
char *go_back_path(char *path, data_t *head, connexion_t *client);
int is_a_file(char *path, data_t *head, connexion_t *client);

#endif /* !UTILS_H_ */
