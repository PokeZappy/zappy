/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** AEntityRaylib.hpp
*/

#pragma once

#include "IEntityRaylib.hpp"
#include "RaylibModels.hpp"

namespace Zappy
{
    class AEntityRaylib : public IEntityRaylib
    {
    public:
        AEntityRaylib(float gridSize) : _gridSize(gridSize) {
            _scale = _gridSize;
        };
    
        void kill(void) { _isDying = true; }
        bool isDying(void) const { return _isDying; }
        float getHeight(void) const { return _altitude; }
        void setHeight(float height) { _altitude = height; }
        void move(raylib::Vector3 vector);
        raylib::Vector3 getPosition(void) const { return raylib::Vector3(_currentPos.x, _altitude, _currentPos.y); }
        float getAnimatedScale(void) const { return _animatedScale; }
    protected:
        float _gridSize;
        Animations::Type _animIndex = Animations::NONE;
        int _animFrame = 0;
        bool _isDying = false;
        float _scale = 1;
        float _animatedScale = 0;
        float _altitude = 0;
        float _height;
        bool _hasIdleAnim = false;
        raylib::Color color;
        raylib::Vector2 offset;
        raylib::Vector2 _currentPos;
    };
}
