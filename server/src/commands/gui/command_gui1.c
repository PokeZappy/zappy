/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_gui1.c
*/

#include "../../../include/commands.h"
#include "../../../include/utils.h"

void cmd_msz(server_t *server, char *args, int client_nbr)
{
    client_socket_t *client = find_client_by_socket(server, client_nbr);

    if (!client || !is_client_gui(client))
        return;
    dprintf(client->socket, "msz %d %d\n", server->grid->_width,
        server->grid->_height);
    printf("msz\n");
}

void cmd_bct(server_t *server, char *args, int client_nbr)
{
    client_socket_t *client = find_client_by_socket(server, client_nbr);
    char **parse_command = decompose_output(args);
    int x = atoi(parse_command[1]);
    int y = atoi(parse_command[2]);
    char *response;

    if (!client || !is_client_gui(client)) {
        free_str_array(parse_command);
        return;
    }
    response = get_tile_content(server->grid->_tiles[y][x]);
    dprintf(client->socket, "bct %d %d %s\n", x, y, response);
    free(response);
    free_str_array(parse_command);
    printf("bct\n");
}

void cmd_mct(server_t *server, char *args, int client_nbr)
{
    client_socket_t *client = find_client_by_socket(server, client_nbr);
    char *response;

    if (!client || !is_client_gui(client))
        return;
    for (int i = 0; i < server->grid->_height; i++) {
        for (int j = 0; j < server->grid->_width; j++) {
            response = get_tile_content(server->grid->_tiles[i][j]);
            dprintf(client->socket, "bct %d %d %s\n", j, i, response);
            free(response);
        }
    }
    printf("mct\n");
}

void cmd_tna(server_t *server, char *args, int client_nbr)
{
    client_socket_t *client = find_client_by_socket(server, client_nbr);
    team_t *current = TAILQ_FIRST(&server->_head_team);

    if (!client || !is_client_gui(client))
        return;
    while (current) {
        dprintf(client->socket, "tna %s\n", current->_name);
        current = TAILQ_NEXT(current, _entries);
    }
    printf("tna\n");
}

void cmd_pnw(server_t *server, char *args, int client_nbr)
{
    printf("pnw\n");
}
