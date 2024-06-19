/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** player_dead.c
*/

#include "../../include/server.h"

void client_dead(server_t *server, client_socket_t *client)
{
    delayed_command_t *delayed_command =
    TAILQ_FIRST(&server->_head_delayed_commands);

    while (delayed_command) {
        if (delayed_command->_client == client) {
            TAILQ_REMOVE(&server->_head_delayed_commands,
            delayed_command, entries);
            free(delayed_command);
            delayed_command = TAILQ_FIRST(&server->_head_delayed_commands);
        } else {
            delayed_command = TAILQ_NEXT(delayed_command, entries);
        }
    }
    dprintf(client->socket, "dead\n");
    dprintf(get_gui(server)->socket, "pdi %d\n", client->_id);
    close(client->socket);
    TAILQ_REMOVE(&server->_head_client_sockets, client, entries);
    free_client(client);
}

void client_eat(server_t *server, client_socket_t *client)
{
    if (client->player->_inventory[0] > 0) {
        client->player->_inventory[0] -= 1;
        client->player->_health = 126;
    } else {
        client_dead(server, client);
    }
}

void check_death(server_t *server)
{
    client_socket_t *client = TAILQ_FIRST(&server->_head_client_sockets);
    client_socket_t *next_client;

    while (client != NULL) {
        next_client = TAILQ_NEXT(client, entries);
        if (!client->player) {
            client = next_client;
            continue;
        }
        if (client->player->_health == 0)
            client_eat(server, client);
        else
            client->player->_health -= 1;
        client = next_client;
    }
}
