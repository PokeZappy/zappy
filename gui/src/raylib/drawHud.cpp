/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** drawHud.cpp
*/

#include "Raylib.hpp"

namespace Zappy {
    void Raylib::drawHud(const World &world) {
        _hudMode->drawBackground(world, _players.size(), _eggs.size());
    }
}
