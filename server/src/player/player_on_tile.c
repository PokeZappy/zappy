/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** player_eject.c
*/

#include "../../include/server.h"

/*player_list_t *get_players_on_same_tile(server_t *server, player_t *current_player) {
    player_list_t *same_tile_players = NULL;
    player_list_t *new_node;
    player_t *player;

    TAILQ_FOREACH(player, &server->_players, _entries) {
        if (player->_pos._x == current_player->_pos._x && player->_pos._y == current_player->_pos._y) {
            new_node = (player_list_t *)malloc(sizeof(player_list_t));
            new_node->player = player;
            new_node->next = same_tile_players;
            same_tile_players = new_node;
        }
    }

    return same_tile_players;
}*/
