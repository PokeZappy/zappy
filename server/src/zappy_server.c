/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** zappy_server.c
*/

#include "../include/server.h"

#include <errno.h>
#include <sys/types.h>

static void free_server(server_t *server)
{
    client_socket_t *client = TAILQ_FIRST(&server->_head_client_sockets);

    if (!server)
        return;
    while (client != NULL) {
        TAILQ_REMOVE(&server->_head_client_sockets, client, entries);
        close(client->socket);
        free(client);
        client = TAILQ_FIRST(&server->_head_client_sockets);
    }
    free(server);
}

static void close_all_clients(server_t *server)
{
    client_socket_t *client = TAILQ_FIRST(&server->_head_client_sockets);

    if (!server)
        return;
    while (client != NULL) {
        TAILQ_REMOVE(&server->_head_client_sockets, client, entries);
        kill(client->pid, SIGTERM);
        close(client->socket);
        free(client);
        client = TAILQ_FIRST(&server->_head_client_sockets);
    }
}

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
    TAILQ_INIT(&server->_head_client_sockets);
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket == -1) {
        fprintf(stderr, "zappy_server: Socket creation failed.\n");
        free_server(server);
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
        free_server(server);
        return 84;
    }
    if (listen(server->socket, arguments->_c) == -1) {
        fprintf(stderr, "zappy_server: Socket listen failed.\n");
        close(server->socket);
        free_server(server);
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
    client_socket_t *new_cl_sckt;
    int client_socket =
        accept(server->socket, (struct sockaddr *)&client_addr, &client_len);

    printf("Client connected: %s:%d\n", inet_ntoa(client_addr.sin_addr),
        ntohs(client_addr.sin_port));
    new_cl_sckt = (client_socket_t *)malloc(sizeof(client_socket_t));
    new_cl_sckt->socket = client_socket;
    pid = fork();
    if (pid == 0) {
        close(server->socket);
        handle_client(client_socket);
    } else if (pid > 0) {
        new_cl_sckt->pid = pid;
        TAILQ_INSERT_TAIL(&server->_head_client_sockets, new_cl_sckt, entries);
        close(client_socket);
    }
}

static int simulate_server(server_t *server)
{
    fd_set readfds;
    struct timeval timeout;
    char buffer[1024];
    int activity;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    FD_SET(server->socket, &readfds);
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    activity = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
    if (FD_ISSET(STDIN_FILENO, &readfds)) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || feof(stdin)) {
            printf("Ctrl+D detected. Exiting...\n");
            return 0;
        }
    }
    if (FD_ISSET(server->socket, &readfds))
        wait_for_client(server);
    return 1;
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
    while (simulate_server(server));
    close_all_clients(server);
    close(server->socket);
    free_server(server);
    return 0;
}
