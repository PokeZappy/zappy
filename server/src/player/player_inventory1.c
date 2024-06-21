/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** player_item.c
*/

#include "../../include/player.h"
#include "../../include/objects.h"

void add_item_to_player(player_t *player, int item, int quantity)
{
    player->_inventory[item] += quantity;
}

void remove_item_from_player(player_t *player, int item, int quantity)
{
    player->_inventory[item] -= quantity;
}

int player_take_item(player_t *player, tiles_t *tile, char *item)
{
    for (int i = 0; i < ITEM_PER_TILE; i++) {
        if ((strncmp(item, object_names[i], strlen(object_names[i])) == 0)
        && tile->_items[i] > 0) {
            add_item_to_player(player, i, 1);
            remove_item_from_tile(tile, i, 1);
            return i;
        }
    }
    return -1;
}

int player_drop_item(player_t *player, tiles_t *tile, char *item)
{
    for (int i = 0; i < ITEM_PER_TILE; i++) {
        if ((strncmp(item, object_names[i], strlen(object_names[i])) == 0)
        && player->_inventory[i] > 0) {
            remove_item_from_player(player, i, 1);
            add_item_to_tile(tile, i, 1);
            return i;
        }
    }
    return -1;
}
