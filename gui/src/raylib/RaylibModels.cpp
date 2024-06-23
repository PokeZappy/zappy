/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** RaylibModels.cpp
*/

#include "RaylibModels.hpp"

namespace Zappy {
    void RaylibModels::update() {
        for (auto &pair : _models) {
            pair.second->updateAnimation(_animations);
        }
    }

    bool RaylibModels::hasAnim(Animations::Type anim) {
        return _models.count(anim) > 0;
    }
}