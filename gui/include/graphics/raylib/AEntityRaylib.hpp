/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** AEntityRaylib.hpp
*/

#pragma once

#include "IEntityRaylib.hpp"

namespace Zappy
{
    class AEntityRaylib : public IEntityRaylib
    {
    public:
        AEntityRaylib(std::string modelPath, size_t gridSize) : _model(modelPath), _gridSize(gridSize) {};
        
        void kill(void) { _isDying = true; }
        bool isDying(void) const { return _isDying; }
        int getAnimationIndex(const std::vector<std::string> &names);
        float getHeight(void) const { return _altitude; }
        void setHeight(float height) { _altitude = height; }
        void move(raylib::Vector3 vector);
        raylib::Vector3 getPosition(void) const { return raylib::Vector3(_currentPos.x, _altitude, _currentPos.y); }
    protected:
        raylib::Model _model;
        size_t _gridSize;
        int _animIndex = -1;
        int _animFrame = 0;
        bool _isDying = false;
        float _scale = 2.0;
        float _altitude;
        float _height = 30;
        bool _hasIdleAnim = false;
        raylib::Color color;
        raylib::Vector2 offset;
        std::vector<raylib::ModelAnimation> _modelAnimations;
        std::unordered_map<std::string, int> _animationIndexes;
        raylib::Image _textImage;
        raylib::Texture2D _textTexture;
        raylib::RenderTexture2D _textRenderTexture;
        raylib::Vector2 _currentPos;
    };
}