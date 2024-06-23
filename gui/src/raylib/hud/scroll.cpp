/*
** EPITECH PROJECT, 2023
** gui
** File description:
** scroll.cpp
*/

#include "HudMode.hpp"

namespace Zappy {
    void HudMode::scrollUp(float wheel) {
        if (_selectedPlayer == nullptr)
            return;
        
        if (_scrollIndex > 0) {
            _howManyScroll += wheel;
            if (_howManyScroll >= 0.5f) {
                _scrollIndex--;
                _selectedPlayer = _selectedPlayers[_scrollIndex];
                _howManyScroll = 0.0f;
            }
        }
    }

    void HudMode::scrollDown(float wheel) {
        if (_selectedPlayer == nullptr)
            return;
        if (_scrollIndex < _selectedPlayers.size() - 1) {
            _howManyScroll += wheel;
            if (_howManyScroll <= -0.5f) {
                _scrollIndex++;
                _selectedPlayer = _selectedPlayers[_scrollIndex];
                _howManyScroll = 0.0f;
            }
        }
    }
}