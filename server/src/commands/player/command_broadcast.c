/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_broadcast.c
*/

#include "../../../include/commands.h"
#include "../../../include/utils.h"

static int return_case_direction(double angle)
{
    if (angle >= 337.5 || angle < 22.5)
        return 1;
    if (angle >= 22.5 && angle < 67.5)
        return 2;
    if (angle >= 67.5 && angle < 112.5)
        return 3;
    if (angle >= 112.5 && angle < 157.5)
        return 4;
    if (angle >= 157.5 && angle < 202.5)
        return 5;
    if (angle >= 202.5 && angle < 247.5)
        return 6;
    if (angle >= 247.5 && angle < 292.5)
        return 7;
    if (angle >= 292.5 && angle < 337.5)
        return 8;
    return -1;
}

static int get_sound_direction(int w, int h, player_t *player, vector_t point)
{
    int dx = point._x - player->_pos._x;
    int dy = point._y - player->_pos._y;
    double angle;

    if (dx == 0 && dy == 0)
        return 0;
    angle = atan2(dy, dx) * 180 / M_PI;
    if (angle < 0)
        angle += 360;
    if (player->_direction == UP)
        angle -= 90;
    if (player->_direction == DOWN)
        angle += 90;
    if (player->_direction == LEFT)
        angle += 180;
    if (angle < 0)
        angle += 360;
    if (angle >= 360)
        angle -= 360;
    return return_case_direction(angle);
}

static int check_for_ko(char *args, client_socket_t *client)
{
    if (strcmp(args, "broadcast") == 0) {
        dprintf(client->socket, "ko\n");
        return 0;
    }
    return 1;
}

void cmd_broadcast(server_t *server, char *args, client_socket_t *client)
{
    char *text = args + 10;
    client_socket_t *current = TAILQ_FIRST(&server->_head_client_sockets);

    if (!check_for_ko(args, client))
        return;
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
