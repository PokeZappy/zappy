/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** free.c
*/

#include "../../include/free.h"
#include "../../include/incantation.h"

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
    if (arguments->n != NULL)
        free_tab(arguments->n);
    free(arguments);
}

void free_client(struct client_socket_s *client)
{
    free_player(client->player);
    free(client);
}

static void free_server_client(server_t *server)
{
    client_socket_t *client = TAILQ_FIRST(&server->head_client_sockets);

    while (client != NULL) {
        TAILQ_REMOVE(&server->head_client_sockets, client, entries);
        close(client->socket);
        free_player(client->player);
        free(client);
        client = TAILQ_FIRST(&server->head_client_sockets);
    }
}

static void free_server_team(server_t *server)
{
    team_t *team = TAILQ_FIRST(&server->head_team);

    while (team != NULL) {
        TAILQ_REMOVE(&server->head_team, team, entries);
        free_team(team);
        team = TAILQ_FIRST(&server->head_team);
    }
}

static void free_server_commands(server_t *server)
{
    delayed_command_t *d = TAILQ_FIRST(&server->head_delayed_commands);

    while (d != NULL) {
        TAILQ_REMOVE(&server->head_delayed_commands, d, entries);
        free(d->args);
        free(d);
        d = TAILQ_FIRST(&server->head_delayed_commands);
    }
}

static void free_incantations(server_t *server)
{
    cmd_incantation_t *incantation = TAILQ_FIRST(&server->head_incantation);

    while (incantation != NULL) {
        TAILQ_REMOVE(&server->head_incantation, incantation, entries);
        free(incantation->participants);
        free(incantation);
        incantation = TAILQ_FIRST(&server->head_incantation);
    }
}

void free_server(server_t *server)
{
    if (!server)
        return;
    free_server_arg(server->arguments);
    free_server_client(server);
    free_server_team(server);
    free_server_commands(server);
    free_incantations(server);
    free_grid(server->grid);
    free(server);
}
