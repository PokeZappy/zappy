/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** player_orientation.c
*/

#include "../../include/player.h"

void player_orientation(player_t *player, bool right)
{
    if (right)
        player->_direction = (direction_t)((player->_direction + 1) % 4);
    else
        player->_direction = (direction_t)((player->_direction + 3) % 4);
}
