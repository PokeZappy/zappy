/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_queue_utils.c
*/

#include "../../../include/commands.h"

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

static int how_many_in_queue(server_t *server, client_socket_t *client)
{
    int count = 0;
    delayed_command_t *delayed_command;

    TAILQ_FOREACH(delayed_command, &server->head_delayed_commands, entries)
        if (delayed_command->client == client)
            count++;
    return count;
}

static timeval_t longest_delay_for_client(server_t *server, client_socket_t *c)
{
    timeval_t longest_delay = {0, 0};
    delayed_command_t *delayed_command = NULL;
    delayed_command_t *tmp = NULL;

    for (delayed_command = TAILQ_FIRST(&server->head_delayed_commands);
        delayed_command != NULL;
        delayed_command = tmp) {
        tmp = TAILQ_NEXT(delayed_command, entries);
        if (delayed_command->client == c
            && compare_timeval(&delayed_command->delay, &longest_delay)) {
            longest_delay = delayed_command->delay;
        }
    }
    return longest_delay;
}

static void calc_delay(server_t *server, client_socket_t *client, timeval_t d)
{
    timeval_t last_delay = longest_delay_for_client(server, client);

    d.tv_sec += last_delay.tv_sec;
    d.tv_usec += last_delay.tv_usec;
    if (d.tv_usec >= 1000000) {
        d.tv_sec += last_delay.tv_usec / 1000000;
        d.tv_usec %= 1000000;
    }
}

static delayed_command_t *last_client_command(server_t *s, client_socket_t *c)
{
    timeval_t longest_delay = {0, 0};
    delayed_command_t *delayed_command = NULL;
    delayed_command_t *tmp = NULL;
    delayed_command_t *last_command = NULL;

    for (delayed_command = TAILQ_FIRST(&s->head_delayed_commands);
        delayed_command != NULL;
        delayed_command = tmp) {
        tmp = TAILQ_NEXT(delayed_command, entries);
        if (delayed_command->client == c
            && compare_timeval(&delayed_command->delay, &longest_delay)) {
            longest_delay = delayed_command->delay;
            last_command = delayed_command;
        }
    }
    return last_command;
}

static void delete_last_cmd(server_t *server, client_socket_t *client)
{
    delayed_command_t *last_command = last_client_command(server, client);

    if (last_command != NULL) {
        TAILQ_REMOVE(&server->head_delayed_commands, last_command, entries);
        free(last_command->args);
        free(last_command);
    }
}

bool icii(server_t *server, client_socket_t *c)
{
    cmd_incantation_t *cmd_incantation =
            TAILQ_FIRST(&server->head_incantation);

    while (cmd_incantation) {
        if (cmd_incantation->organizer == c)
            return true;
        if (is_participant(cmd_incantation, c))
            return true;
        cmd_incantation = TAILQ_NEXT(cmd_incantation, entries);
    }
    return false;
}

void add_icii_delay(server_t *s, client_socket_t *c, delayed_command_t *d)
{
    delayed_command_t *current;
    timeval_t current_time;
    long delay_ms;

    if (icii(s, c)) {
        current = ficbcq(s, c);
        if (!current)
            return;
        if (!strncmp(d->args, "Incantation", 11))
            return;
        gettimeofday(&current_time, NULL);
        delay_ms = (current->delay.tv_sec - current_time.tv_sec) * 1000000 +
        (current->delay.tv_usec - current_time.tv_usec);
        add_seconds(&d->delay, delay_ms / 1000000.0);
    }
}

void add_delay(server_t *server, client_socket_t *c, delayed_command_t *delay)
{
    if (how_many_in_queue(server, c) < 10) {
        if (how_many_in_queue(server, c) != 0)
            calc_delay(server, c, delay->delay);
    } else {
        delete_last_cmd(server, c);
        calc_delay(server, c, delay->delay);
    }
    add_icii_delay(server, c, delay);
}
