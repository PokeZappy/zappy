/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** EggRaylib.hpp
*/

#pragma once

#include "raylib-cpp.hpp"
#include "Utils.hpp"
#include "Egg.hpp"
#include <unordered_map>

namespace Zappy {
    class EggRaylib {
    public:
        EggRaylib(const std::shared_ptr<Egg> egg, size_t gridSize);
};
}