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

void free_client(struct client_socket_s *client)
{
    free_player(client->player);
    free(client);
}

static void free_server_client(server_t *server)
{
    client_socket_t *client = TAILQ_FIRST(&server->_head_client_sockets);

    while (client != NULL) {
        TAILQ_REMOVE(&server->_head_client_sockets, client, entries);
        close(client->socket);
        free_player(client->player);
        free(client);
        client = TAILQ_FIRST(&server->_head_client_sockets);
    }
}

static void free_server_team(server_t *server)
{
    team_t *team = TAILQ_FIRST(&server->_head_team);

    while (team != NULL) {
        TAILQ_REMOVE(&server->_head_team, team, _entries);
        free_team(team);
        team = TAILQ_FIRST(&server->_head_team);
    }
}

static void free_egg_list(server_t *server)
{
    egg_t *egg = TAILQ_FIRST(&server->_head_egg);
    egg_t *tmp_egg;

    while (egg != NULL) {
        tmp_egg = TAILQ_NEXT(egg, _entries);
        TAILQ_REMOVE(&server->_head_egg, egg, _entries);
        free(egg);
        egg = tmp_egg;
    }
}

void free_server(server_t *server)
{
    if (!server)
        return;
    free_server_arg(server->arguments);
    free_server_client(server);
    free_server_team(server);
    free_grid(server->grid);
    free_egg_list(server);
    free(server);
}
