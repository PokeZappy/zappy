/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** player_level.c
*/

#include "../../include/player.h"

int get_player_level(player_t *player)
{
    return player->_level;
}

int increment_player_level(player_t *player)
{
    player->_level++;
    return player->_level;
}
