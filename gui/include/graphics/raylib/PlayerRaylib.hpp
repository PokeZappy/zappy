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
        PlayerRaylib() = default;
        PlayerRaylib(const std::shared_ptr<Player> &worldPlayer, PokemonInfo &pkInfo);

        void draw(void);

        raylib::Color color;
        raylib::Vector2 offset;
        const std::shared_ptr<Player> worldPlayer;
    private:
        float getRotation(void) const;
        raylib::Model _model;
        PokemonInfo infos;
        std::vector<raylib::ModelAnimation> _modelAnimation;
        int _animIndex = 0;
        int _animFrame = 0;
        raylib::Vector2 _lastPos;
    };
} // namespace Zappy
