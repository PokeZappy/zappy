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
        Team(const std::string &name) : _name(name) {}
        ~Team() = default;

        const std::string &getName() const { return _name; }
    private:
        std::string _name;
        // std::vector<Player *> _players;
        // std::vector<std::shared_ptr<Player>> _players;
        // std::vector<size_t> _playersId;

        // std::vector<Player> _players;
        // std::vector<Eggs> _eggs;
    };
} // namespace Zappy
