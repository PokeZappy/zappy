/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** direction.h
*/

#pragma once

typedef enum direction_e {
    UP,
    RIGHT,
    DOWN,
    LEFT
} direction_t;

direction_t get_right_direction(direction_t direction);
direction_t get_left_direction(direction_t direction);
