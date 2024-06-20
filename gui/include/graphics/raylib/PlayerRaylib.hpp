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

namespace Zappy {
    class PlayerRaylib : public AEntityRaylib {
    public:
        PlayerRaylib(const std::shared_ptr<Player> &worldPlayer, PokemonInfo &pkInfo, size_t gridSize);
        void draw(const raylib::Camera camera);
        void update(void);
        void loadTextureAndModel(void);
        const std::shared_ptr<Player> worldPlayer;
        PokemonInfo infos;
    private:
        float getRotation(void) const;

        size_t _currentOrientation;
        size_t _level = 1;
        float _verticalRotation = 0.0;
    };
} // namespace Zappy
