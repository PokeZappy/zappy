/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** PlayerRaylib.cpp
*/

#include "PlayerRaylib.hpp"

namespace Zappy
{
    PlayerRaylib::PlayerRaylib(const std::shared_ptr<Player> &worldPlayer, const std::string &modelPath, size_t gridSize)
        : worldPlayer(worldPlayer), _model(modelPath), _gridSize(gridSize) {
            color = raylib::Color::White();
            _modelAnimation = raylib::ModelAnimation::Load(modelPath);

            // offset = raylib::Vector2(
            //     static_cast<float>(rand() % (GRID_SIZE / 4) - (GRID_SIZE / 2)),
            //     static_cast<float>(rand() % (GRID_SIZE / 4) - (GRID_SIZE / 2)));
            offset = raylib::Vector2(0, 0);
            _currentPos = raylib::Vector2(worldPlayer->getX(), worldPlayer->getY());
        }

    float PlayerRaylib::getRotation(void) const
    {
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

    void PlayerRaylib::draw(void)
    {
        // update
        _animFrame++;
        raylib::Vector2 posGoal = raylib::Vector2(worldPlayer->getX(), worldPlayer->getY());
        _currentPos += (posGoal - _currentPos) / 10;
        _animIndex = 1;
        if (std::abs(_currentPos.x - posGoal.x) < 0.01 && std::abs(_currentPos.y - posGoal.y) < 0.01) {
            _currentPos = posGoal;
            // _animFrame = 0;
        }
        if (_currentPos == posGoal) {
            _animIndex = 0;
            // _animFrame = 0;
        }

        float rotationGoal = getRotation();
        _currentOrientation += (rotationGoal - _currentOrientation) / 5;

        // draw
        _model.UpdateAnimation(_modelAnimation[_animIndex], _animFrame).Draw
        (raylib::Vector3{
            _currentPos.x * _gridSize + offset.x, 0,
            _currentPos.y * _gridSize + offset.y},
            raylib::Vector3(0, 1, 0), _currentOrientation);
    }
} // namespace Zappy
