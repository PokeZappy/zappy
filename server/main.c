/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** main.c
*/

#include "include/error_handling.h"

int main(int ac, char **av)
{
    int error = error_handling(ac, av);

    if (error == 84)
        return 84;
    if (error == 1)
        return 0;
    return 0;
}
