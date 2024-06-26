/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** zappy_server.c
*/

#include "../include/server.h"

static void close_all_clients(server_t *server)
{
    client_socket_t *client = TAILQ_FIRST(&server->head_client_sockets);

    if (!server)
        return;
    while (client != NULL) {
        close(client->socket);
        client = TAILQ_NEXT(client, entries);
    }
}

static void init_all_teams(server_t *server)
{
    char **teams = server->arguments->n;
    int max_clients = server->arguments->c;
    team_t *team;

    TAILQ_INIT(&server->head_team);
    TAILQ_INIT(&server->head_incantation);
    for (int i = 0; teams[i]; i++) {
        team = init_team(teams[i], max_clients);
        if (team) {
            TAILQ_INSERT_TAIL(&server->head_team, team, entries);
        } else {
            fprintf(stderr, "init_all_teams: Init team ko: %s\n", teams[i]);
        }
    }
}

static int init_server(server_t *server, server_arg_t *arguments)
{
    server->arguments = arguments;
    server->socket = -1;
    memset(&server->sock_in, 0, sizeof(server->sock_in));
    FD_ZERO(&server->read_fds);
    FD_ZERO(&server->write_fds);
    TAILQ_INIT(&server->head_client_sockets);
    TAILQ_INIT(&server->head_delayed_commands);
    TAILQ_INIT(&server->head_egg);
    server->grid = init_grid(server, arguments->x, arguments->y);
    init_all_teams(server);
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket == -1) {
        fprintf(stderr, "zappy_server: Socket creation failed.\n");
        free_server(server);
        return 84;
    }
    server->sock_in.sin_family = AF_INET;
    server->sock_in.sin_addr.s_addr = INADDR_ANY;
    server->sock_in.sin_port = htons(arguments->p);
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
    if (listen(server->socket, arguments->c) == -1) {
        fprintf(stderr, "zappy_server: Socket listen failed.\n");
        close(server->socket);
        free_server(server);
        return 84;
    }
    printf("Server is running on port %d\n", arguments->p);
    return 0;
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
    client = TAILQ_FIRST(&server->head_client_sockets);
    while (client != NULL) {
        FD_SET(client->socket, &readfds);
        if (client->socket > max_sd)
            max_sd = client->socket;
        client = TAILQ_NEXT(client, entries);
    }
    return handle_client(server, max_sd, readfds);
}

void block_incoming_signal(server_t *server)
{
    signal(SIGPIPE, SIG_IGN);
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
    block_incoming_signal(server);
    while (simulate_server(server));
    close_all_clients(server);
    close(server->socket);
    free_server(server);
    return 0;
}
