/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** PlayerRaylib.hpp
*/

#pragma once

#include "Utils.hpp"
#include "Player.hpp"
#include "PokemonInfo.hpp"
#include "AEntityRaylib.hpp"
#include "rgif.hpp"

namespace Zappy {
    class PlayerRaylib : public AEntityRaylib {
    public:
        PlayerRaylib(const std::shared_ptr<Player> &worldPlayer, PokemonInfo &pkInfo, std::shared_ptr<RaylibModels> models, float gridSize);
        void draw(const raylib::Camera &camera, bool selectionMode);
        void update(void);
        void updateModels(std::shared_ptr<RaylibModels> models);

        const std::shared_ptr<Player> worldPlayer;
        PokemonInfo infos;
    private:
        float getRotation(void) const;

        std::shared_ptr<RaylibModels> &_models;
        size_t _currentOrientation;
        size_t _level = 0;
        float _verticalRotation = 0.0;
        Incantation _graphicalIncantingState = Incantation::NONE;
        raylib::Gif _successGif;
        raylib::Gif _failureGif;
    };
} // namespace Zappy
