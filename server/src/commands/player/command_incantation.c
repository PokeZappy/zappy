/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_incantation.c
*/

#include "../../../include/commands.h"
#include "../../../include/incantation.h"

void cmd_pre_incant(server_t *server, char *args, client_socket_t *client)
{
    command_t cmd = {"incantation", cmd_post_incant, 300};
    player_t *player = client->player;

    if (check_incantation(server, player) == false) {
        dprintf(client->socket, "ko\n");
        return;
    }
    dprintf(client->socket, "Elevation underway\n");
    actl(server, client, &cmd, args);
}

void cmd_post_incant(server_t *server, char *args, client_socket_t *client)
{
    player_t *player = client->player;
    incantation_t incantation = incantations[player->_level - 1];

    for (int i = 0; i < 7; i++)
        player->_inventory[i] -= incantation._objects_required[i];
    player->_level++;
    dprintf(client->socket, "Current level: %d\n", player->_level);
}
