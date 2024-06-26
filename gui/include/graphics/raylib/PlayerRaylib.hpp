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
        PlayerRaylib(const std::shared_ptr<Player> worldPlayer,
            PokemonInfo &pkInfo, std::shared_ptr<RaylibModels> models,
            float gridSize, raylib::Color teamColor, const raylib::Gif &broadcastGif,
            const raylib::Gif &successGif, const raylib::Gif &failureGif,
            const raylib::Gif &followGif, const raylib::Gif &pushGif);
        void draw(bool isHudMode);
        void drawPantheon(raylib::Vector3 position);
        void update(void);
        void updateModels(std::shared_ptr<RaylibModels> models);

        raylib::Vector3 getPixelPos(void) const;
        void drawGifs(const Camera &camera);
        void drawFollowGif(const Camera &camera);

        void glow(void);

        const std::shared_ptr<Player> worldPlayer;
        PokemonInfo infos;
    private:
        float getRotation(void) const;

        std::shared_ptr<RaylibModels> _models;
        size_t _currentOrientation;
        size_t _level = 0;
        float _verticalRotation = 0.0;
        std::string _broadcastMessage;
        raylib::Gif _broadcastGif;
        Incantation _graphicalIncantingState = Incantation::NONE;
        raylib::Gif _successGif;
        raylib::Gif _failureGif;
        raylib::Gif _followGif;
        raylib::Gif _pushGif;
    };
} // namespace Zappy
