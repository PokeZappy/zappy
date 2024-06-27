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

void player_orientation(player_t *player, bool right)
{
    if (right)
        player->direction = (direction_t)((player->direction + 1) % 4);
    else
        player->direction = (direction_t)((player->direction + 3) % 4);
}

int nb_player_on_tile(server_t *server, vector_t tilepos)
{
    int nb = 0;
    client_socket_t *current = TAILQ_FIRST(&server->head_client_sockets);
    vector_t pos;

    while (current) {
        if (!current->player) {
            current = TAILQ_NEXT(current, entries);
            continue;
        }
        pos = current->player->pos;
        if (pos.x == tilepos.x && pos.y == tilepos.y)
            nb++;
        current = TAILQ_NEXT(current, entries);
    }
    return nb;
}
