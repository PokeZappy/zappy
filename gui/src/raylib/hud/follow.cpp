/*
** EPITECH PROJECT, 2023
** gui
** File description:
** follow.cpp
*/

#include "HudMode.hpp"

namespace Zappy {

    void HudMode::followTarget(raylib::Camera &camera) {
        if (_targetedPlayer != nullptr) {
            camera.target = _targetedPlayer->getPosition() * _gridSize;
        }
    }

    void HudMode::setFirstPokemonTarget() {
        if (_selectedPlayers.size() == 0)
            return;
        _targetedPlayer = _selectedPlayers[0];
    }
}