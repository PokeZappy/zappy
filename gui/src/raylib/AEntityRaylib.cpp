/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** AEntityRaylib.cpp
*/

#include "AEntityRaylib.hpp"

namespace Zappy {
    void AEntityRaylib::move(raylib::Vector3 vector)
    {
        _currentPos.x += vector.x;
        _currentPos.y += vector.z;
        _altitude = vector.y;
    }
}
