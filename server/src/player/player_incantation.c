/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** incantation.c
*/

#include "../../include/incantation.h"
#include "../../include/server.h"
#include "../../include/utils.h"

int player_same_pos_and_level(server_t *server, player_t *player)
{
    client_socket_t *current;
    int number = 0;

    TAILQ_FOREACH(current, &server->_head_client_sockets, entries) {
        if (!current->player)
            continue;
        if (current->player->_pos._x == player->_pos._x &&
            current->player->_pos._y == player->_pos._y &&
            current->player->_level == player->_level)
            number++;
    }
    return number;
}

bool check_incantation(server_t *server, player_t *player)
{
    incantation_t incantation = incantations[player->_level - 1];
    int players = 0;
    tiles_t *tile = server->grid->_tiles[player->_pos._y][player->_pos._x];

    for (int i = 0; i < 7; i++) {
        if (tile->_items[i] < incantation._objects_required[i])
            return false;
    }
    players = player_same_pos_and_level(server, player);
    if (players < incantation._players_required)
        return false;
    return true;
}

//break_player_queue(server, current);
client_socket_t **rip(server_t *server, player_t *player)
{
    int players_count = player_same_pos_and_level(server, player);
    client_socket_t **participants = (client_socket_t **)
    calloc(players_count, sizeof(player_t *));
    client_socket_t *current = TAILQ_FIRST(&server->_head_client_sockets);
    int i = 0;

    while (current) {
        if (!current->player)
            continue;
        if (current->player->_pos._x == player->_pos._x &&
            current->player->_pos._y == player->_pos._y &&
            current->player->_level == player->_level) {
            participants[i] = find_client_by_player(server, current->player);
            i++;
        }
        current = TAILQ_NEXT(current, entries);
    }
    return participants;
}

void create_current_incantation(server_t *server, player_t *player)
{
    cmd_incantation_t *cmd_incantation = (cmd_incantation_t *)
    malloc(sizeof(cmd_incantation_t));
    vector_t pos = {player->_pos._y, player->_pos._x};

    cmd_incantation->organizer = find_client_by_player(server, player);
    cmd_incantation->_level = player->_level;
    cmd_incantation->tile_vector = pos;
    cmd_incantation->participants = rip(server, player);
    cmd_incantation->number_of_participants =
    player_same_pos_and_level(server, player);
    TAILQ_INSERT_TAIL(&server->_head_incantation, cmd_incantation, entries);
}
