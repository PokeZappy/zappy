/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** list.h
*/

#pragma once

#include "stdlib.h"

typedef struct list_s {
    void *data;
    struct list_s *next;
    struct list_s *prev;
} list_t;

list_t *init_list(void *data);
void free_list(list_t *list);
void append_list(list_t *list, void *data);
