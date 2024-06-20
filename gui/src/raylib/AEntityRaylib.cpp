/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** AEntityRaylib.cpp
*/

#include "AEntityRaylib.hpp"

namespace Zappy {
    int AEntityRaylib::getAnimationIndex(const std::vector<std::string> &names)
    {
        for (size_t i = 0; i < _modelAnimations.size(); i++) {
            std::string animName(_modelAnimations[i].name);
            for (size_t j = 0; j < names.size(); j++) {
                if (animName.find(names[j]) != std::string::npos) {
                    return i;
                }
            }
        }
        return -1;
    }

    void AEntityRaylib::move(raylib::Vector3 vector)
    {
        _currentPos.x += vector.x;
        _currentPos.y += vector.z;
        _altitude = vector.y;
    }
}