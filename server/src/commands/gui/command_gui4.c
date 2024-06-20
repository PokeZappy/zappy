/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_gui4.c
*/

#include "../../../include/commands.h"
#include "../../../include/utils.h"

void cmd_sgt(server_t *server, char *args, client_socket_t *client)
{
    char message[256];

    snprintf(message, sizeof(message), "sgt %d\n", server->arguments->_f);
    send_gui_message(client->socket, message);
    printf("sgt\n");
}
