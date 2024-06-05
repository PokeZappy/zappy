/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** incantation.c
*/

#include "../../include/incantation.h"
#include "../../include/server.h"

bool check_incantation(server_t *server, player_t *player)
{
    incantation_t incantation = incantations[player->_level - 1];
    int players = 0;
    int objects[7] = {0};

    for (int i = 0; i < 7; i++)
        objects[i] = player->_inventory[i];
    for (int i = 0; i < 7; i++) {
        if (objects[i] < incantation._objects_required[i])
            return false;
    }
    for (client_socket_t *current = TAILQ_FIRST(&server->_head_client_sockets);
        current; current = TAILQ_NEXT(current, entries)) {
        if (current->player->_level == player->_level)
            players++;
    }
    if (players < incantation._players_required)
        return false;
    return true;
}
