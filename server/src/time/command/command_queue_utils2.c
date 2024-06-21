/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_queue_utils2.c
*/

#include "../../../include/commands.h"
#include "../../../include/server.h"

void add_seconds(timeval_t *time, float seconds)
{
    long microseconds = lround(seconds * 1000000);

    time->tv_usec += microseconds;
    if (time->tv_usec >= 1000000) {
        time->tv_sec += time->tv_usec / 1000000;
        time->tv_usec %= 1000000;
    }
}

bool compare_timeval(timeval_t *a, timeval_t *b)
{
    return ((a->tv_sec == b->tv_sec) ?
    (a->tv_usec > b->tv_usec) : (a->tv_sec > b->tv_sec));
}

bool is_time_g_or_e(timeval_t *current_time, timeval_t *delay_time)
{
    return ((current_time->tv_sec == delay_time->tv_sec) ?
            (current_time->tv_usec >= delay_time->tv_usec) :
            (current_time->tv_sec >= delay_time->tv_sec));
}

bool icii(server_t *server, client_socket_t *c)
{
    cmd_incantation_t *cmd_incantation =
    TAILQ_FIRST(&server->_head_incantation);

    while (cmd_incantation) {
        if (cmd_incantation->organizer == c)
            return true;
        if (player_is_participant(cmd_incantation, c))
            return true;
        cmd_incantation = TAILQ_NEXT(cmd_incantation, entries);
    }
    return false;
}

void add_delay(server_t *server, client_socket_t *c, delayed_command_t *delay)
{
    delayed_command_t *current;
    timeval_t current_time;
    long delay_ms;

    if (how_many_in_queue(server, c) < 10) {
        if (how_many_in_queue(server, c) != 0)
            calc_delay(server, c, delay->_delay);
    } else {
        delete_last_cmd(server, c);
        calc_delay(server, c, delay->_delay);
    }
    add_icii_delay(server, c, delay);
}
