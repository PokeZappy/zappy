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
#include "PokemonInfo.hpp"

namespace Zappy {
    class PlayerRaylib {
    public:
        PlayerRaylib(const std::shared_ptr<Player> &worldPlayer, PokemonInfo &pkInfo, size_t gridSize);
        void draw(void);
        void update(void);
        float getHeight(void) const { return _height; }
        void setHeight(float height) { _height = height; }
        void move(raylib::Vector3 vector);
        bool isDying(void) const { return _isDying; }
        void kill(void) { _isDying = true; }
        void loadTextureAndModel(void);

        raylib::Vector3 getPosition(void) const { return raylib::Vector3(_currentPos.x, _height, _currentPos.y); }

        raylib::Color color;
        raylib::Vector2 offset;
        const std::shared_ptr<Player> worldPlayer;
        PokemonInfo infos;
    private:
        float getRotation(void) const;
        raylib::Model _model;
        std::vector<raylib::ModelAnimation> _modelAnimation;
        int _animIndex = 0;
        int _animFrame = 0;
        raylib::Vector2 _currentPos;
        float _height;
        size_t _currentOrientation;

        bool _isDying = false;
        float _scale = 0.5;

        size_t _gridSize;
    };
} // namespace Zappy
