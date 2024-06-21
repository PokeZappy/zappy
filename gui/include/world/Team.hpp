/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Team.hpp
*/

#pragma once

namespace Zappy {
    class Eggs {

    };

    enum TeamType {
        FIRE,
        GRASS,
        WATER,
        STEEL,
        FAIRY,
        SIZE,
    };
    class Team {
    public:
        Team() = default;
        Team(const std::string &name, TeamType type = TeamType::SIZE) : _name(name), _type(type) {}
        ~Team() = default;

        const std::string &getName() const { return _name; }
        TeamType getType() const { return _type; }
    private:
        std::string _name;
        TeamType _type = TeamType::SIZE;
    };
} // namespace Zappy
