/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** player_item.c
*/

#include "../../include/player.h"
#include <stdlib.h>
#include <stdio.h>

static const char *items[] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
};

char *print_player_inventory(player_t *player)
{
    char *result = (char *)malloc(sizeof(char) * 1024);

    sprintf(result, "[");
    for (int i = 0; i < ITEM_PER_TILE; i++) {
        sprintf(result, "%s%s %d", result, items[i], player->_inventory[i]);
        if (i != 6)
            sprintf(result, "%s, ", result);
    }
    sprintf(result, "%s]\n", result);
    return result;
}

void add_item_to_player(player_t *player, int item, int quantity)
{
    player->_inventory[item] += quantity;
}

void remove_item_from_player(player_t *player, int item, int quantity)
{
    player->_inventory[item] -= quantity;
}

void player_take_item(player_t *player, tiles_t *tile, int item)
{
    if (tile->_items[item] > 0) {
        add_item_to_player(player, item, 1);
        remove_item_from_tile(tile, item, 1);
    }
}

void player_drop_item(player_t *player, tiles_t *tile, int item)
{
    if (player->_inventory[item] > 0) {
        add_item_to_tile(tile, item, 1);
        remove_item_from_player(player, item, 1);
    }
}
