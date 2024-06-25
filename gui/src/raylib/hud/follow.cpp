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

    void HudMode::setSelectedPlayerToTarget() {
        auto it = std::find(_selectedPlayers.begin(), _selectedPlayers.end(), _targetedPlayer);

        if (it != _selectedPlayers.end()) {
            _scrollIndex = std::distance(_selectedPlayers.begin(), it);
            _selectedPlayer = _targetedPlayer;
        } else {
            _scrollIndex = 0;
            _selectedPlayer = _selectedPlayers[0];
        }
    }
}
