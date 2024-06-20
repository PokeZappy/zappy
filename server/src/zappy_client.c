/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** zappy_server.c
*/

#include "../include/client.h"

static void send_client_message(int socket, const char *msg)
{
    size_t message_len = strlen(msg);

    if (send(socket, msg, message_len, 0) == -1) {
        fprintf(stderr, "send_message: Send failed.\n");
        close(socket);
        exit(EXIT_FAILURE);
    }
}

static void close_all_clients(struct server_s *server)
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

static void handle_gui_client(client_socket_t *client, struct server_s *server)
{
    int x = server->grid->_width;
    int y = server->grid->_height;

    client->_is_gui = 1;
    cmd_msz(server, NULL, get_gui(server));
    cmd_sgt(server, NULL, get_gui(server));
    cmd_mct(server, NULL, get_gui(server));
    cmd_tna(server, NULL, get_gui(server));
}

static void handle_client_cmd(char *commands, client_socket_t *client,
    struct server_s *server)
{
    player_t *new_player;
    int client_socket = client->socket;

    if (client->player == NULL && client->_is_gui == 0) {
        if (strcmp(commands, "GRAPHIC") == 0) {
            handle_gui_client(client, server);
            return;
        }
        client->player = add_player_to_team(commands, server);
        if (client->player == NULL) {
            fprintf(stderr, "handle_client_cmd: Enable to create player\n");
            return;
        }
        dprintf(client->socket, "%d\n%d %d\n", get_client_rest(client->player
            ->_team), client->player->_pos._x, client->player->_pos._y);
        cmd_pnw(server, NULL, client);
    }
    if (client->_is_gui == 0)
        return manage_cmd_play(commands, client, server);
    manage_cmd_gui(commands, client, server);
}

static void handle_client_message(client_socket_t *client,
    struct server_s *server)
{
    int client_socket = client->socket;
    char buffer[READ_SIZE];
    int bytes = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

    if (bytes == -1) {
        fprintf(stderr, "handle_client_message: Receive failed.\n");
        close(client_socket);
        return;
    }
    if (bytes == 0) {
        printf("Client disconnected\n");
        close(client_socket);
        return;
    }
    buffer[bytes - 2] = '\0';
    printf("Received from {%d}: {%s}\n", client->_id, buffer);
    handle_client_cmd(buffer, client, server);
}

static int loop_all_client(struct server_s *server, fd_set readfds)
{
    client_socket_t *tmp;
    client_socket_t *client;

    client = TAILQ_FIRST(&server->_head_client_sockets);
    while (client != NULL) {
        tmp = TAILQ_NEXT(client, entries);
        if (FD_ISSET(client->socket, &readfds))
            handle_client_message(client, server);
        client = tmp;
    }
    time_manager(server);
    return 1;
}

static void wait_for_client(struct server_s *server)
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
    new_client->_is_gui = 0;
    new_client->_id = ntohs(client_addr.sin_port);
    new_client->player = NULL;
    TAILQ_INSERT_TAIL(&server->_head_client_sockets, new_client, entries);
    send_client_message(client_socket, "WELCOME\n");
}

int handle_client(struct server_s *server, int max_sd, fd_set readfds)
{
    struct timeval timeout;
    int activity;
    char buffer[READ_SIZE];

    timeout.tv_sec = 0;
    timeout.tv_usec = 1;
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
