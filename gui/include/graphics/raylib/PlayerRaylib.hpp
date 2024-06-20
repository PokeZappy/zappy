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
#include <unordered_map>

namespace Zappy {
    class PlayerRaylib {
    public:
        PlayerRaylib(const std::shared_ptr<Player> &worldPlayer, PokemonInfo &pkInfo, size_t gridSize);
        void draw(const raylib::Camera camera);
        void update(void);
        float getHeight(void) const { return _altitude; }
        void setHeight(float height) { _altitude = height; }
        void move(raylib::Vector3 vector);
        bool isDying(void) const { return _isDying; }
        void kill(void) { _isDying = true; }
        void loadTextureAndModel(void);
        int getAnimationIndex(const std::vector<std::string> &names);

        raylib::Vector3 getPosition(void) const { return raylib::Vector3(_currentPos.x, _altitude, _currentPos.y); }

        raylib::Color color;
        raylib::Vector2 offset;
        const std::shared_ptr<Player> worldPlayer;
        PokemonInfo infos;
    private:
        float getRotation(void) const;
        size_t _gridSize;

        raylib::Model _model;
        std::vector<raylib::ModelAnimation> _modelAnimation;
        int _animIndex = -1;
        int _animFrame = 0;
        raylib::Vector2 _currentPos;
        float _altitude;
        float _height = 30;
        size_t _currentOrientation;
        bool _hasIdleAnim = false;

        std::unordered_map<std::string, int> _animationIndexes;

        bool _isDying = false;
        float _verticalRotation = 0.0;
        float _scale = 2.0;
        size_t _level = 1;

        raylib::Image _textImage;
        raylib::Texture2D _textTexture;
        raylib::RenderTexture2D _textRenderTexture;

    };
} // namespace Zappy
