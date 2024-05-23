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

void free_server(server_t *server)
{
    client_socket_t *client = TAILQ_FIRST(&server->_head_client_sockets);

    if (!server)
        return;
    free_server_arg(server->arguments);
    while (client != NULL) {
        TAILQ_REMOVE(&server->_head_client_sockets, client, entries);
        close(client->socket);
        free(client);
        client = TAILQ_FIRST(&server->_head_client_sockets);
    }
    free(server);
}
