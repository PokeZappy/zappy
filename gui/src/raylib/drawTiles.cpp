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
        // drawItem(5, 5, 1, tiles[5][5].getItem(1));
        _itemModel.UpdateAnimation(_itemAnimations[1], _itemAnimationFrame);
        // _itemAnimationFrame++;

        for (size_t y = 0; y < tiles.size(); y++) {
            for (size_t x = 0; x < tiles[y].size(); x++) {
                    drawItem(x, y, 1, tiles[y][x].getItem(1));
                for (size_t i = 0; i < 7; i++) {
                    // std::cout << std::to_string(tiles[y][x].getItem(i)) << std::endl;
                    // _resourcesText.setPosition(width * _tileWidth + 10,
                    //     height * _tileHeight + i * 13);
                    // _resourcesText.setFillColor(getItemColor(static_cast<Item>(i)));
                    // _window.draw(_resourcesText);
                }
            }
        }
    }

    void Raylib::drawItem(size_t x, size_t y, size_t id, size_t quantity)
    {
        _shader.BeginMode();
        // std::cout << "mesh count :" << _itemModel.meshCount << ", materialCount : " << _itemModel.materialCount << ", BonesCount : " << _itemModel.boneCount << std::endl;
        // for (size_t b = 0; b < _itemModel.boneCount; b++) {
        //     std::cout << "Bone " << b << " : " << _itemModel.bones[b].name << std::endl;
        // }
        // for (size_t i = 0; i < _itemModel.meshCount; i++) {
        //     for (size_t j = 0; j < _itemModel.materialCount; j++) {
        //         DrawMesh(_itemModel.meshes[i], _itemModel.materials[j], MatrixMultiply(MatrixScale(10, 10, 10), MatrixTranslate(x * _gridSize + (i * 10), 0.0f, y * _gridSize + (j * 10))));
        //     }
        // //    DrawMesh(_itemModel.meshes[i], _itemModel.materials[0], MatrixTranslate(x * _gridSize + i, 0.0f, y * _gridSize));
        // }
        // _itemModel.meshes[0].
        // _itemAnimationFrame++;
        // float random1 = rand() % 20 - 10;
        // float random2 = rand() % 20 - 10;
        float random1 = 0;
        float random2 = 0;
        // _itemModel.UpdateAnimation(_itemAnimations[0], _itemAnimationFrame).Draw(raylib::Vector3(x * _gridSize, 0, y * _gridSize), 10.0f, raylib::Color::White());
        _itemModel.Draw(raylib::Vector3(x * _gridSize + random1, 10, y * _gridSize + random2), 10.0f, raylib::Color::White());
        _shader.EndMode();
    }
} // namespace Zappy
