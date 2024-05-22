/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** free.c
*/

#include "../../include/free.h"

static void free_tab(char **tab)
{
    for (int i = 0; tab[i]; i++)
        free(tab[i]);
    free(tab);
}

void free_server_arg(server_arg_t *arguments)
{
    if (arguments == NULL)
        return;
    if (arguments->_n != NULL)
        free_tab(arguments->_n);
    free(arguments);
}
