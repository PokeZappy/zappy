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
    enum class Orientation {
        NONE,
        NORTH,
        EAST,
        SOUTH,
        WEST
    };
    class Color {
    public:
        Color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}
        Color() : r(0), g(0), b(0) {}
        unsigned char r;
        unsigned char g;
        unsigned char b;
    };
}
