/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** updateMouse.cpp
*/

#include "Sfml.hpp"

namespace Zappy
{
    void Sfml::updateMouse(void)
    {
        _mousePositions.window = sf::Mouse::getPosition(_window);
        _window.setView(_view);
        _mousePositions.view = _window.mapPixelToCoords(_mousePositions.window);
        if (_mousePositions.view.x >= 0.0f && _tileWidth > 0.0f)
            _mousePositions.grid.x = _mousePositions.view.x / _tileWidth;
        if (_mousePositions.view.y >= 0.0f && _tileHeight > 0.0f)
            _mousePositions.grid.y = _mousePositions.view.y / _tileHeight;
        _tileSelector.setPosition(_mousePositions.grid.x * _tileWidth, _mousePositions.grid.y * _tileHeight);
    }
} // namespace Zappy
