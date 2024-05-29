/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Tools.hpp
*/

#pragma once

#include <string>
#include <memory.h>

namespace Zappy {
    enum Orientation {
        NONE,
        NORTH,
        EAST,
        SOUTH,
        WEST
    };
    static std::string getOrientationString(Orientation orientation) {
        switch (orientation) {
            case Orientation::NORTH: return "NORTH";
            case Orientation::EAST: return "EAST";
            case Orientation::SOUTH: return "SOUTH";
            case Orientation::WEST: return "WEST";
            default: return "NONE";
        }
    }
}
