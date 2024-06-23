/*
** EPITECH PROJECT, 2023
** gui
** File description:
** scroll.cpp
*/

#include "HudMode.hpp"

namespace Zappy {
    void HudMode::scrollUp() {
        if (_selectedPlayer == nullptr)
            return;
        if (_scrollIndex > 0) {
            _scrollIndex--;
            _selectedPlayer = _selectedPlayers[_scrollIndex];
        }
    }

    void HudMode::scrollDown() {
        if (_selectedPlayer == nullptr)
            return;
        if (_scrollIndex < _selectedPlayers.size()) {
            _scrollIndex++;
        }
    }
}