/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** drawTiles.cpp
*/

#include "Raylib.hpp"

namespace Zappy
{
    void Raylib::drawTiles(const std::vector<std::vector<Tile>> &tiles)
    {
        _rockModel.UpdateAnimation(_rockAnimations[0], _rockAnimationFrame);

        float x_pos = 0;
        float y_pos = 0;
        for (size_t y = 0; y < tiles.size(); y++) {
            for (size_t x = 0; x < tiles[y].size(); x++) {
                x_pos = x * _gridSize - _gridSize / 4;
                y_pos = y * _gridSize - _gridSize / 4;
                drawFood(x_pos, y_pos, tiles[y][x].getItem(0));
                for (size_t i = 1; i < 7; i++) {
                    drawRock(x_pos, y_pos, i, tiles[y][x].getItem(i));
                }
            }
        }
    }

    void Raylib::drawFood(float x, float y, size_t quantity)
    {
        for (size_t i = 0; i < std::clamp(quantity, (size_t)0, (size_t)7); i++)
            _foodModel.Draw(raylib::Vector3(x + i * 3, 2, y), raylib::Vector3(1, 0, 0),
                0, raylib::Vector3(4.0f, 4.0f, 4.0f));
    }

    void Raylib::drawRock(float x, float y, size_t id, size_t quantity)
    {
        _shader.BeginMode();
        _rockModel.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = _rockTextures[id - 1];
        for (size_t i = 0; i < std::clamp(quantity, (size_t)0, (size_t)5); i++)
            _rockModel.Draw(raylib::Vector3(x + i * 3, 0, y + id * 5), 4.0f);
        _shader.EndMode();
    }
} // namespace Zappy
