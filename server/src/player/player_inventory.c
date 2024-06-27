/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** player_item.c
*/

#include "../../include/player.h"
#include "../../include/objects.h"

static void add_item_to_player(player_t *player, int item)
{
    player->inventory[item] += 1;
}

static void remove_item_from_player(player_t *player, int item)
{
    player->inventory[item] -= 1;
}

static void add_item_to_tile(tiles_t *tile, int item, int quantity)
{
    tile->items[item] += quantity;
}

static void remove_item_from_tile(tiles_t *tile, int item, int quantity)
{
    tile->items[item] -= quantity;
}

int player_take_item(player_t *player, tiles_t *tile, char *item)
{
    for (int i = 0; i < ITEM_PER_TILE; i++) {
        if ((strncmp(item, object_names[i], strlen(object_names[i])) == 0)
        && tile->items[i] > 0) {
            add_item_to_player(player, i);
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
        && player->inventory[i] > 0) {
            remove_item_from_player(player, i);
            add_item_to_tile(tile, i, 1);
            return i;
        }
    }
    return -1;
}

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
