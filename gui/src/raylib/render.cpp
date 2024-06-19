/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** render.cpp
*/

#include "Raylib.hpp"

namespace Zappy
{
    void Raylib::render(const World &world)
    {
        (void)world;
        raylib::Color textColor = raylib::Color::Black();
        raylib::Ray ray(GetMousePosition(), _camera);
        _window.BeginDrawing();
        {
            _window.ClearBackground(raylib::Color::SkyBlue());
            _window.DrawFPS();
            // 3D scene

            _camera.BeginMode();

            for (int x = 0; x < _mapX; x++)
            {
                for (int z = 0; z < _mapY; z++)
                {
                    raylib::RayCollision meshHit = ray.GetCollision(_floorMesh, MatrixTranslate(x * _gridSize, 0.0f, z * _gridSize));
                    if (meshHit.hit)
                    {
                        DrawMesh(_floorMesh, _hitGridMaterial, MatrixTranslate(x * _gridSize, 0.0f, z * _gridSize));
                    }
                    else
                    {
                        DrawMesh(_floorMesh, _floorMaterial, MatrixTranslate(x * _gridSize, 0.0f, z * _gridSize));
                    }
                }
            }

            drawTiles(world.getTiles());

            for (auto &player : _players)
            {
                player->draw(_camera);
            }

            _tv.Draw(raylib::Vector3(_mapX / 2 * _gridSize - 50, 80, -(float)(_gridSize * 4)), 2000);

            _camera.EndMode();
            // end of 3D scene
            textColor.DrawText(raylib::Vector3(_camera.GetPosition()).ToString(), 50, 50, 25);
            textColor.DrawText(raylib::Vector3(_camera.GetTarget()).ToString(), 50, 80, 25);
        }
        _window.EndDrawing();
    }
}
