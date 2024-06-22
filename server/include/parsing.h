/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** parsing.h
*/

#pragma once

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int _p; // port number
    int _x; // width of the world
    int _y; // height of the world
    int _c; // number of authorized clients per team
    int _f; // reciprocal of time unit for execution of actions
    char **_n; // name of the team member

    int _num_names; // How many names there are ?
} server_arg_t;

server_arg_t *parsing(int ac, char **av);
