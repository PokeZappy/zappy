/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_player2.c
*/

#include "../../../include/commands.h"
#include "../../../include/utils.h"

static int get_sound_direction(int w, int h, player_t *player, vector_t point)
{
    direction_t direction = player->_direction;
    int dx = point._x - player->_pos._x;
    int dy = point._y - player->_pos._y;
    int relative_dir;
    int dir;

    if (dx > w / 2)
        dx -= w;
    if (dx < -w / 2)
        dx += w;
    if (dy > h / 2)
        dy -= h;
    if (dy < -h / 2)
        dy += h;
    dir = (int)round((atan2(-dy, dx)) / (M_PI / 4));
    if (dir < 0)
        dir += 8;
    relative_dir = (8 + dir - direction * 2) % 8;
    return (relative_dir == 0) ? 8 : relative_dir;
}

void cmd_broadcast(server_t *server, char *args, client_socket_t *client)
{
    char *text = args + 10;
    client_socket_t *current = TAILQ_FIRST(&server->_head_client_sockets);

    while (current != NULL) {
        if (current->_id == client->_id) {
            current = TAILQ_NEXT(client, entries);
            continue;
        }
        dprintf(current->socket, "message %d, %s\n",
            get_sound_direction(server->grid->_width, server->grid->_height,
            current->player, client->player->_pos), text);
        current = TAILQ_NEXT(current, entries);
    }
    dprintf(client->socket, "ok\n");
}

void cmd_eject(server_t *server, char *args, client_socket_t *client)
{
    printf("eject\n");
}

void cmd_take(server_t *server, char *args, client_socket_t *client)
{
    player_t *player = client->player;
    char **parse_args = decompose_output(args);
    int object_taken = atoi(parse_args[1]);
    int result;

    if (!player) {
        free_str_array(parse_args);
        return;
    }
    result = player_take_item(player,
    server->grid->_tiles[player->_pos._y][player->_pos._y], object_taken);
    if (result == 0)
        dprintf(client->socket, "ok\n");
    else
        dprintf(client->socket, "ko\n");
    free_str_array(parse_args);
    printf("take\n");
}

void cmd_set(server_t *server, char *args, client_socket_t *client)
{
    player_t *player = client->player;
    char **parse_args = decompose_output(args);
    int object_set = atoi(parse_args[1]);
    int result;

    if (!player) {
        free_str_array(parse_args);
        return;
    }
    result = player_take_item(player,
    server->grid->_tiles[player->_pos._y][player->_pos._y], object_set);
    if (result == 0)
        dprintf(client->socket, "ok\n");
    else
        dprintf(client->socket, "ko\n");
    free_str_array(parse_args);
    printf("set\n");
}

void cmd_incantation(server_t *server, char *args, client_socket_t *client)
{
    printf("incantation\n");
}
