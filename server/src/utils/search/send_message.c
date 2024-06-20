/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** find_by_socket.c
*/

#include "../../../include/server.h"

void send_gui_message(int socket, const char *msg)
{
    size_t message_len = strlen(msg);

    if (send(socket, msg, message_len, 0) == -1) {
        fprintf(stderr, "send_message: Send failed.\n");
        close(socket);
        exit(EXIT_FAILURE);
    }
}
