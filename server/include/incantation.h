/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** incantation.h
*/

#pragma once

typedef struct incantation_s {
    int _level;
    int _players_required;
    int _objects_required[7];
} incantation_t;

static const incantation_t incantations[] = {
    {1, 1, {0, 1, 0, 0, 0, 0, 0}},
    {2, 2, {0, 1, 1, 1, 0, 0, 0}},
    {3, 2, {0, 2, 0, 1, 0, 2, 0}},
    {4, 4, {0, 1, 1, 2, 0, 1, 0}},
    {5, 4, {0, 1, 2, 1, 3, 0, 0}},
    {6, 6, {0, 1, 2, 3, 0, 1, 0}},
    {7, 6, {0, 2, 2, 2, 2, 2, 1}},
};
