/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_player3.c
*/

#include "../../../include/commands.h"

void cmd_slot(server_t *server, char *args, client_socket_t *client)
{
    printf("slot_available\n");
}

void cmd_fork(server_t *server, char *args, client_socket_t *client)
{
    printf("fork\n");
}

void cmd_dead(server_t *server, char *args, client_socket_t *client)
{
    printf("dead\n");
}
