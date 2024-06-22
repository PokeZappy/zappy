/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_queue_utils2.c
*/

#include "../../../include/commands.h"

void add_icii_delay(server_t *s, client_socket_t *c, delayed_command_t *d)
{
    delayed_command_t *current;
    timeval_t current_time;
    long delay_ms;

    if (icii(s, c)) {
        current = ficbcq(s, c);
        if (!current)
            return;
        if (!strncmp(d->_args, "Incantation", 11))
            return;
        gettimeofday(&current_time, NULL);
        delay_ms = (current->_delay.tv_sec - current_time.tv_sec) * 1000000 +
        (current->_delay.tv_usec - current_time.tv_usec);
        add_seconds(&d->_delay, delay_ms / 1000000.0);
    }
}
