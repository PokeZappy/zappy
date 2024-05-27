/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_player3.c
*/

#include "../../../include/commands.h"
#include "../../../include/utils.h"

void cmd_slot(server_t *server, char *args, int client_nbr)
{
    printf("slot_available\n");
}

void cmd_fork(server_t *server, char *args, int client_nbr)
{
    printf("fork\n");
}

void cmd_dead(server_t *server, char *args, int client_nbr)
{
    printf("dead\n");
}

void cmd_connect_nbr(server_t *server, char *args, int client_nbr)
{
    player_t *player = find_player_by_socket(server, client_nbr);

    if (!player)
        return;
    dprintf(client_nbr, "%d\n", player->_team->_max_clients - player->_team->_current_clients);
    printf("connect_nbr\n");
}
