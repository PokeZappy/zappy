/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Team.hpp
*/

#pragma once

#include "Tools.hpp"
#include "Player.hpp"

namespace Zappy {
    class Eggs {

    };
    class Team {
    public:
        Team() = default;
        ~Team() = default;
    private:
        std::string _name;
        std::vector<Player> _players;
        std::vector<Eggs> _eggs;
    };
} // namespace Zappy
