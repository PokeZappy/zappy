/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_player1.c
*/

#include "../../../include/commands.h"
#include "../../../include/utils.h"

void cmd_forward(server_t *server, char *args, int client_nbr)
{
    player_t *player = find_player_by_socket(server, client_nbr);

    if (!player)
        return;
    player_move(player);
    dprintf(client_nbr, "ok\n");
    printf("forward\n");
}

void cmd_right(server_t *server, char *args, int client_nbr)
{
    player_t *player = find_player_by_socket(server, client_nbr);

    if (!player)
        return;
    player_orientation(player, 1);
    dprintf(client_nbr, "ok\n");
    printf("right\n");
}

void cmd_left(server_t *server, char *args, int client_nbr)
{
    player_t *player = find_player_by_socket(server, client_nbr);

    if (!player)
        return;
    player_orientation(player, 0);
    printf("left\n");
}

void cmd_look(server_t *server, char *args, int client_nbr)
{
    printf("look\n");
}

void cmd_inventory(server_t *server, char *args, int client_nbr)
{
    player_t *player = find_player_by_socket(server, client_nbr);
    char *response;

    if (!player)
        return;
    response = print_player_inventory(player);
    dprintf(client_nbr, "%s\n", response);
    free(response);
    printf("inventory\n");
}
