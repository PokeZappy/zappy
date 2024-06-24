/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** player_movement.c
*/

#include "../../include/player.h"

void check_playerposition(player_t *player, int map_width, int map_height)
{
    if (player->pos.x < 0)
        player->pos.x = map_width - 1;
    if (player->pos.x >= map_width)
        player->pos.x = 0;
    if (player->pos.y < 0)
        player->pos.y = map_height - 1;
    if (player->pos.y >= map_height)
        player->pos.y = 0;
}

void player_move(player_t *player, int map_width, int map_height)
{
    if (player->direction == UP)
        player->pos.y -= 1;
    if (player->direction == DOWN)
        player->pos.y += 1;
    if (player->direction == LEFT)
        player->pos.x -= 1;
    if (player->direction == RIGHT)
        player->pos.x += 1;
    check_playerposition(player, map_width, map_height);
}
