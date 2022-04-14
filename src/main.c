/*
** EPITECH PROJECT, 2022
** Project
** File description:
** main
*/

#include "init_ftp.h"
#include "macro.h"

int main(int ac, char **av)
{
    int return_value = init_ftp(ac, av);

    if (return_value == FTP_ERROR)
        return PROGRAM_ERROR;
    return PROGRAM_SUCCESS;
}
