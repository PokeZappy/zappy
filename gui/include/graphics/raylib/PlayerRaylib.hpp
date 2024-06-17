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
        PlayerRaylib() = default;
        PlayerRaylib(const std::shared_ptr<Player> &worldPlayer, const std::string &modelPath)
        : worldPlayer(worldPlayer), _model(modelPath) {
            color = raylib::Color::White();
            _modelAnimation = raylib::ModelAnimation::Load(modelPath);

            offset =  raylib::Vector2(static_cast<float>(rand() % 10 - 5),
                static_cast<float>(rand() % 10 - 5));
            // offset = raylib::Vector2(0, 0);
        }

        void draw(void)
        {
            _animFrame++;
            _model.UpdateAnimation(_modelAnimation[0], _animFrame).Draw
            (raylib::Vector3{
                worldPlayer->getX() * GRID_SIZE + offset.x, 0,
                worldPlayer->getY() * GRID_SIZE + offset.y},
                raylib::Vector3(0, 1, 0), getRotation());
        }

        raylib::Color color;
        raylib::Vector2 offset;
        const std::shared_ptr<Player> worldPlayer;
    private:
        float getRotation(void) const {
            switch (worldPlayer->getOrientation()) {
                case Orientation::NORTH:
                    return 180;
                case Orientation::EAST:
                    return 270;
                case Orientation::SOUTH:
                    return 0;
                case Orientation::WEST:
                    return 90;
            }
            return 0;
        }
        raylib::Model _model;
        std::vector<raylib::ModelAnimation> _modelAnimation;
        int _animFrame = 0;
    };
} // namespace Zappy
