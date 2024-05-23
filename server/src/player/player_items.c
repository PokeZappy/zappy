/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** player_item.c
*/

#include "../../include/player.h"

void add_item_to_player(player_t *player, int item, int quantity)
{
    player->_inventory[item] += quantity;
}

void remove_item_from_player(player_t *player, int item, int quantity)
{
    player->_inventory[item] -= quantity;
}
