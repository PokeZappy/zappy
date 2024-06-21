/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** player_look.c
*/

#include "../../include/server.h"

char *player_look(server_t *server, player_t *player)
{
    char *result = (char *)malloc(sizeof(char) * 4096);

    sprintf(result, "[");
    for (int i = 0; i <= player->_level; i++) {
        player_look_loop(server, player, i, result);
    }
    sprintf(result, "%s]", result);
    return result;
}
