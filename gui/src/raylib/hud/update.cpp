/*
** EPITECH PROJECT, 2023
** gui
** File description:
** update.cpp
*/

#include "HudMode.hpp"

namespace Zappy {
    void HudMode::update(raylib::Camera &camera) {
        if (_selectedPlayer == nullptr) {
            return;
        }
        if (IsKeyPressed(KEY_ONE)) {

        }
        if (IsKeyPressed(KEY_TWO)) {
            if (_targetedPlayer == _selectedPlayer)
                _targetedPlayer = nullptr;
            else
                _targetedPlayer = _selectedPlayer;
        }
        if (IsKeyPressed(KEY_THREE)) {

        }
        if (IsKeyPressed(KEY_FOUR)) {

        }
    }
}