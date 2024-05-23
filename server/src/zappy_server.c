/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** zappy_server.c
*/


#include "../include/server.h"

static void close_all_clients(server_t *server)
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

static void handle_client_cmd(char *commands, int cl_sckt, int *cl_close)
{
    if (strcmp(commands, "EXIT") == 0) {
        printf("Client requested exit\n");
        close(cl_sckt);
        *cl_close = 1;
    }
}

static void handle_client_message(int cl_sckt, server_t *server, int *cl_close)
{
    char buffer[READ_SIZE];
    int bytes = recv(cl_sckt, buffer, sizeof(buffer) - 1, 0);

    if (bytes == -1) {
        fprintf(stderr, "handle_client_message: Receive failed.\n");
        close(cl_sckt);
        *cl_close = 1;
        return;
    }
    if (bytes == 0) {
        printf("Client disconnected\n");
        close(cl_sckt);
        *cl_close = 1;
        return;
    }
    buffer[bytes - 2] = '\0';
    printf("Received from client: {%s}\n", buffer);
    handle_client_cmd(buffer, cl_sckt, cl_close);
}

static void wait_for_client(server_t *server)
{
    client_socket_t *new_client;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_socket =
        accept(server->socket, (struct sockaddr *)&client_addr, &client_len);

    if (client_socket < 0) {
        fprintf(stderr, "accept failed: %s\n", strerror(errno));
        return;
    }
    printf("Client connected: %s:%d\n",
        inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    new_client = (client_socket_t *)malloc(sizeof(client_socket_t));
    new_client->socket = client_socket;
    TAILQ_INSERT_TAIL(&server->_head_client_sockets, new_client, entries);
}

static int loop_all_client(server_t *server, fd_set readfds)
{
    int client_closed;
    client_socket_t *tmp;
    client_socket_t *client;

    client = TAILQ_FIRST(&server->_head_client_sockets);
    while (client != NULL) {
        tmp = TAILQ_NEXT(client, entries);
        if (FD_ISSET(client->socket, &readfds)) {
            client_closed = 0;
            handle_client_message(client->socket, server, &client_closed);
            if (client_closed) {
                TAILQ_REMOVE(&server->_head_client_sockets, client, entries);
                free(client);
            }
        }
        client = tmp;
    }
    return 1;
}

static int handle_client(server_t *server, int max_sd, fd_set readfds)
{
    struct timeval timeout;
    int activity;
    char buffer[READ_SIZE];

    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    activity = select(max_sd + 1, &readfds, NULL, NULL, &timeout);
    if (activity < 0 && errno != EINTR) {
        fprintf(stderr, "select error: %s\n", strerror(errno));
        return 0;
    }
    if (FD_ISSET(STDIN_FILENO, &readfds)) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || feof(stdin)) {
            printf("Ctrl+D detected. Exiting...\n");
            return 0;
        }
    }
    if (FD_ISSET(server->socket, &readfds))
        wait_for_client(server);
    return loop_all_client(server, readfds);
}

static int simulate_server(server_t *server)
{
    fd_set readfds;
    client_socket_t *client;
    int max_sd;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    FD_SET(server->socket, &readfds);
    max_sd = server->socket;
    client = TAILQ_FIRST(&server->_head_client_sockets);
    while (client != NULL) {
        FD_SET(client->socket, &readfds);
        if (client->socket > max_sd)
            max_sd = client->socket;
        client = TAILQ_NEXT(client, entries);
    }
    return handle_client(server, max_sd, readfds);
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
