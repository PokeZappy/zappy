/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** player_item.c
*/

#include "../../include/player.h"
#include "../../include/objects.h"

char *print_player_inventory(player_t *player)
{
    char *result = (char *)malloc(sizeof(char) * 1024);

    sprintf(result, "[ ");
    for (int i = 0; i < ITEM_PER_TILE; i++) {
        sprintf(result, "%s%s %d", result, object_names[i],
        player->inventory[i]);
        if (i != 6)
            sprintf(result, "%s, ", result);
    }
    sprintf(result, "%s ]", result);
    return result;
}


char *get_player_inventory(player_t *player)
{
    char *content = (char *)malloc(sizeof(char) * 1024);

    sprintf(content, "%d %d %d %d %d %d %d", player->inventory[0],
        player->inventory[1], player->inventory[2], player->inventory[3],
        player->inventory[4], player->inventory[5], player->inventory[6]);
    return content;
}
