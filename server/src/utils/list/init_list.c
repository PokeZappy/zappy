/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** init_list.c
*/

#include "../../../include/list.h"

list_t *init_list(void)
{
    list_t *list = (list_t *)malloc(sizeof(list_t));

    if (!list)
        return NULL;
    list->data = NULL;
    list->next = list;
    list->prev = list;
    return list;
}

void append_list(list_t *list, void *data)
{
    list_t *new_node = (list_t *)malloc(sizeof(list_t));

    if (!new_node)
        return;
    new_node->data = data;
    new_node->next = list;
    new_node->prev = list->prev;
    list->prev->next = new_node;
    list->prev = new_node;
}

void free_list(list_t *list)
{
    list_t *tmp = list->next;
    list_t *next;

    while (tmp != list) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(list);
}
