/*
** EPITECH PROJECT, 2023
** gui
** File description:
** follow.cpp
*/

#include "HudMode.hpp"

namespace Zappy {

    CameraMode HudMode::followTarget(raylib::Camera &camera) {
        if (_targetedPlayer != nullptr) {
            camera.target = _targetedPlayer->getPosition() * _gridSize;
            _targetedPlayer->glow();
            return CAMERA_THIRD_PERSON;
        }
        return CAMERA_FIRST_PERSON;
    }

    void HudMode::setFirstPokemonTarget() {
        if (_selectedPlayers.size() == 0)
            return;
        _targetedPlayer = _selectedPlayers[0];
    }

    void HudMode::applySelectedPlayerToTarget() {
        _targetedPlayer = _selectedPlayer;
    }
}
