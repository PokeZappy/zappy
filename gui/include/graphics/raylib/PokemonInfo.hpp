/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** PokemonInfo.hpp
*/

#pragma once

#include <iostream>
#include <vector>

namespace Zappy
{
    class PokemonInfo
    {
    public:
        bool shiny;
        std::string displayName;
        std::string id;
        int stage;
        std::vector<PokemonInfo> evolutions;
    };
}