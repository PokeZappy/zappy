/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** player_movement.c
*/

#include "../../include/player.h"

void check_player_position(player_t *player, int map_width, int map_height)
{
    if (player->_pos._x < 0)
        player->_pos._x = map_width - 1;
    if (player->_pos._x >= map_width)
        player->_pos._x = 0;
    if (player->_pos._y < 0)
        player->_pos._y = map_height - 1;
    if (player->_pos._y >= map_height)
        player->_pos._y = 0;
}

void player_move(player_t *player, int map_width, int map_height)
{
    if (player->_direction == UP)
        player->_pos._y -= 1;
    if (player->_direction == DOWN)
        player->_pos._y += 1;
    if (player->_direction == LEFT)
        player->_pos._x -= 1;
    if (player->_direction == RIGHT)
        player->_pos._x += 1;
    check_player_position(player, map_width, map_height);
}
