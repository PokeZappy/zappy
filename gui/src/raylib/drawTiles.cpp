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
        _rockModel.UpdateAnimation(_rockAnimations[_rockAnimationIndex], _rockAnimationFrame);
        _rockAnimationFrame++;
        if (_rockAnimationFrame >= _rockAnimations[_rockAnimationIndex].frameCount) {
            _rockAnimationIndex = rand() % 9 + 3;
            _rockAnimationFrame = 0;
        }

        raylib::Ray ray(GetMousePosition(), _camera);

        float x_pos = 0;
        float y_pos = 0;
        for (size_t y = 0; y < tiles.size(); y++) {
            for (size_t x = 0; x < tiles[y].size(); x++) {
                if (!_hudMode->activated()) {
                    DrawMesh(_floorMesh, _floorMaterial, MatrixTranslate(x * _gridSize, 0.0f, y * _gridSize));
                } else {
                    raylib::RayCollision meshHit = ray.GetCollision(_floorMesh, MatrixTranslate(x * _gridSize, 0.0f, y * _gridSize));
                    if (meshHit.hit) {
                        _hudMode->setTile(std::make_unique<Tile>(tiles[y][x]));
                        DrawMesh(_floorMesh, _hitGridMaterial, MatrixTranslate(x * _gridSize, 0.0f, y * _gridSize));
                    } else {
                        DrawMesh(_floorMesh, _floorMaterial, MatrixTranslate(x * _gridSize, 0.0f, y * _gridSize));
                    }
                }

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
        float scale = _gridSize / 6;
        for (size_t i = 0; i < std::clamp(quantity, (size_t)0, (size_t)7); i++)
            _foodModel.Draw(raylib::Vector3(x + i * 3, scale / 2.2, y), raylib::Vector3(1),
                0, raylib::Vector3(scale, true));
    }

    void Raylib::drawRock(float x, float y, size_t id, size_t quantity)
    {
        float scale = _gridSize / 8;
        _rockModel.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = _rockTextures[id - 1];
        for (size_t i = 0; i < std::clamp(quantity, (size_t)0, (size_t)5); i++)
            _rockModel.Draw(raylib::Vector3(x + i * _gridSize / 10, 0, y + id * _gridSize / 10), scale);
    }
} // namespace Zappy
