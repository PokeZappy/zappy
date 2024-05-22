/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** zappy_server.c
*/

#include "../include/client.h"

static void send_welcome_message(int socket)
{
    char message[] = "Received from server: Welcome !\n";

    if (send(socket, message, sizeof(message), 0) == -1) {
        fprintf(stderr, "send_message: Send failed.\n");
        close(socket);
        exit(EXIT_FAILURE);
    }
}

static void handle_command(char *buffer, int client_socket, server_t *server)
{
    if (strcmp(buffer, "EXIT") == 0) {
        printf("Client requested exit\n");
        close(client_socket);
        free_server(server);
        exit(EXIT_SUCCESS);
    }
}

void handle_client(int client_socket, server_t *server)
{
    char buffer[READ_SIZE];
    int bytes;

    send_welcome_message(client_socket);
    while (1) {
        bytes = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes == -1) {
            fprintf(stderr, "handle_client: Receive failed.\n");
            close(client_socket);
            exit(EXIT_FAILURE);
        }
        if (bytes == 0) {
            printf("Client disconnected\n");
            close(client_socket);
            exit(EXIT_SUCCESS);
        }
        buffer[bytes - 2] = '\0';
        printf("Received from client: {%s}\n", buffer);
        handle_command(buffer, client_socket, server);
    }
}
