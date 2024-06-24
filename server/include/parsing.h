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
    int p; // port number
    int x; // width of the world
    int y; // height of the world
    int c; // number of authorized clients per team
    int f; // reciprocal of time unit for execution of actions
    char **n; // name of the team member

    int num_names; // How many names there are ?
} server_arg_t;

server_arg_t *parsing(int ac, char **av);
