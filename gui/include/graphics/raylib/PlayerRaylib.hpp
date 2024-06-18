/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** PlayerRaylib.hpp
*/

#pragma once

#include "raylib-cpp.hpp"
#include "Utils.hpp"
#include "Player.hpp"

namespace Zappy {
    class PlayerRaylib {
    public:
        PlayerRaylib(const std::shared_ptr<Player> &worldPlayer, const std::string &modelPath, size_t gridSize);

        void draw(void);

        raylib::Color color;
        raylib::Vector2 offset;
        const std::shared_ptr<Player> worldPlayer;
    private:
        float getRotation(void) const;
        raylib::Model _model;
        std::vector<raylib::ModelAnimation> _modelAnimation;
        int _animIndex = 0;
        int _animFrame = 0;
        raylib::Vector2 _currentPos;
        size_t _currentOrientation;

        size_t _gridSize;
    };
} // namespace Zappy
