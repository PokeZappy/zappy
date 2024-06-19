/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** str_to_word_array.c
*/

#include "stdlib.h"
#include "string.h"

char **decompose_output(char *output)
{
    char **result = (char **)malloc(sizeof(char *) * 1024);
    char *token;
    int i = 0;

    token = strtok(output, " ");
    while (token != NULL) {
        result[i] = (char *)malloc(strlen(token) + 1);
        strcpy(result[i], token);
        i++;
        token = strtok(NULL, " ");
    }
    result[i - 1][strlen(result[i - 1])] = '\0';
    result[i] = NULL;
    return result;
}

void free_str_array(char **array)
{
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}
