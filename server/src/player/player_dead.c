/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** player_dead.c
*/

#include "../../include/server.h"

void client_dead(server_t *server, client_socket_t *client)
{
    delayed_command_t *delayed_command;

    TAILQ_FOREACH(delayed_command, &server->_head_delayed_commands, entries) {
        if (delayed_command->_client == client) {
            TAILQ_REMOVE(&server->_head_delayed_commands,
            delayed_command, entries);
            free(delayed_command);
        }
    }
    dprintf(client->socket, "dead\n");
    close(client->socket);
    TAILQ_REMOVE(&server->_head_client_sockets, client, entries);
    free_player(client->player);
    free(client);
}

void client_eat(server_t *server, client_socket_t *client)
{
    if (client->player->_inventory[0] > 0) {
        client->player->_inventory[0] -= 1;
        client->player->_health = 126;
    } else
        client_dead(server, client);
}

void check_death(server_t *server)
{
    client_socket_t *client;

    TAILQ_FOREACH(client, &server->_head_client_sockets, entries) {
        if (!client->player)
            continue;
        if (client->player->_health == 0)
            client_eat(server, client);
        else
            client->player->_health -= 1;
    }
}
