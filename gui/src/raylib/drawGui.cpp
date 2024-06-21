/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** drawGui.cpp
*/

#include "Raylib.hpp"

namespace Zappy {
    void Raylib::drawGui(const World &world) {
        _hudMode->drawBackground();
    }
}