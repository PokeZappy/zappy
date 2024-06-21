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
        PlayerRaylib(const std::shared_ptr<Player> &worldPlayer, PokemonInfo &pkInfo,
            size_t gridSize, raylib::Shader &shader);
        void draw(const raylib::Camera camera, bool selectionMode);
        void update(void);
        void loadTextureAndModel(raylib::Shader &shader);

        void loadShinyTexture(void);
        int getAnimationIndex(const std::vector<std::string> &names);
        const std::shared_ptr<Player> worldPlayer;
        PokemonInfo infos;
    private:
        float getRotation(void) const;

        raylib::Model _model;
        std::vector<raylib::ModelAnimation> _modelAnimations;
        size_t _currentOrientation;
        size_t _level = 0;
        float _verticalRotation = 0.0;
    };
} // namespace Zappy
