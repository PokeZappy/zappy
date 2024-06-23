/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** AEntity.cpp
*/

#include "world/AEntity.hpp"
#include "Team.hpp"

namespace Zappy {

    AEntity::AEntity(size_t id, size_t x, size_t y, const Team &team) : _id(id), _x(x), _y(y), _team(team) {

    }
};
