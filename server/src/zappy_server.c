/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** zappy_server.c
*/

#include "../include/server.h"

static int init_server(server_t *server, server_arg_t *arguments)
{
    server->arguments = arguments;
    server->socket = -1;
    memset(&server->sock_in, 0, sizeof(server->sock_in));
    FD_ZERO(&server->read_fds);
    FD_ZERO(&server->write_fds);
    server->grid = NULL;
    TAILQ_INIT(&server->_head_player);
    TAILQ_INIT(&server->_head_team);
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket == -1) {
        fprintf(stderr, "zappy_server: Socket creation failed.\n");
        free(server);
        return 84;
    }
    server->sock_in.sin_family = AF_INET;
    server->sock_in.sin_addr.s_addr = INADDR_ANY;
    server->sock_in.sin_port = htons(arguments->_p);
    return 0;
}

static int connect_server(server_t *server, server_arg_t *arguments)
{
    if (bind(server->socket, (struct sockaddr *)&server->sock_in,
        sizeof(server->sock_in)) == -1) {
        fprintf(stderr, "zappy_server: Socket bind failed.\n");
        close(server->socket);
        free(server);
        return 84;
    }
    if (listen(server->socket, arguments->_c) == -1) {
        fprintf(stderr, "zappy_server: Socket listen failed.\n");
        close(server->socket);
        free(server);
        return 84;
    }
    printf("Server is running on port %d\n", arguments->_p);
    return 0;
}

static void wait_for_client(server_t *server)
{
    pid_t pid;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_socket =
        accept(server->socket, (struct sockaddr *)&client_addr, &client_len);

    if (client_socket == -1) {
        fprintf(stderr, "zappy_server: Accept failed.\n");
        return;
    }
    printf("Client connected: %s:%d\n", inet_ntoa(client_addr.sin_addr),
        ntohs(client_addr.sin_port));
    pid = fork();
    if (pid == 0) {
        close(server->socket);
        handle_client(client_socket);
    } else if (pid > 0) {
        close(client_socket);
    }
}

int zappy_server(server_arg_t *arguments)
{
    server_t *server = (server_t *)malloc(sizeof(server_t));

    if (server == NULL) {
        fprintf(stderr, "zappy_server: Memory allocation of server failed.\n");
        return 84;
    }
    if (init_server(server, arguments) == 84 ||
        connect_server(server, arguments) == 84) {
        return 84;
    }
    while (1) {
        wait_for_client(server);
    }
    close(server->socket);
    free(server);
    return 0;
}
