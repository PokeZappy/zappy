/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_queue_utils2.c
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

bool is_time_g_or_e(timeval_t *current_time, timeval_t *delay_time)
{
    return ((current_time->tv_sec == delay_time->tv_sec) ?
            (current_time->tv_usec >= delay_time->tv_usec) :
            (current_time->tv_sec >= delay_time->tv_sec));
}
