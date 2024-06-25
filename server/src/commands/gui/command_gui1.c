/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_gui1.c
*/

#include "../../../include/commands.h"
#include "../../../include/utils.h"

void cmd_msz(server_t *server, char *args, client_socket_t *client)
{
    if (!client || !is_client_gui(client))
        return;
    dprintf(client->socket, "msz %d %d\n", server->grid->width,
        server->grid->height);
}

void cmd_bct(server_t *server, char *args, client_socket_t *client)
{
    char **parse_command = decompose_output(args);
    int x = atoi(parse_command[1]);
    int y = atoi(parse_command[2]);
    char *response;

    if (!client || !is_client_gui(client)) {
        free_str_array(parse_command);
        return;
    }
    response = get_tile_content(server->grid->tiles[y][x]);
    dprintf(client->socket, "bct %d %d %s\n", x, y, response);
    free(response);
    free_str_array(parse_command);
}

void cmd_mct(server_t *server, char *args, client_socket_t *client)
{
    char *response;

    if (!client || !is_client_gui(client))
        return;
    for (int i = 0; i < server->grid->height; i++) {
        for (int j = 0; j < server->grid->width; j++) {
            response = get_tile_content(server->grid->tiles[i][j]);
            dprintf(client->socket, "bct %d %d %s\n", j, i, response);
            free(response);
        }
    }
}

void cmd_tna(server_t *server, char *args, client_socket_t *client)
{
    team_t *current = TAILQ_FIRST(&server->head_team);

    if (!client || !is_client_gui(client))
        return;
    while (current) {
        dprintf(client->socket, "tna %s\n", current->name);
        current = TAILQ_NEXT(current, entries);
    }
}

void cmd_pnw(server_t *server, char *args, client_socket_t *client)
{
    int id = client->id;
    int x = client->player->pos.x;
    int y = client->player->pos.y;
    int o = client->player->direction + 1;
    int l = client->player->level;
    char *n = client->player->team->name;
    client_socket_t *gui_socket = get_gui(server);

    if (gui_socket)
        dprintf(gui_socket->socket,
        "pnw %d %d %d %d %d %s\n", id, x, y, o, l, n);
}
