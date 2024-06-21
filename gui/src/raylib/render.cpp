/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** render.cpp
*/

#include "Raylib.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

namespace Zappy
{
    void Raylib::render(const World &world)
    {
        _hudMode->getTile() = nullptr;
        (void)world;
        if (debugMode->activated()) {
            renderDebug(world);
            return;
        }
        raylib::Color textColor = raylib::Color::Black();
        raylib::Ray ray(GetMousePosition(), _camera);
        _window.BeginDrawing();
        {
            _window.ClearBackground(raylib::Color::SkyBlue());
            // 3D scene

            _camera.BeginMode();
            _shader.BeginMode();

            _tv.Draw(raylib::Vector3(_mapX / 2 * _gridSize - 50, 80, -(float)(_gridSize * 4)), 2000);
            float scale = 400;
            _arena.Draw(raylib::Vector3(_mapX / 2 * _gridSize, -35, _mapY / 2 * _gridSize),
                raylib::Vector3(1, 0, 0), -90, raylib::Vector3(scale, scale, scale));

            _sun.Draw(_lights[0].position, 10);
            _moon.Draw(_lights[1].position, 20);

            for (int x = 0; x < _mapX; x++) {
                for (int z = 0; z < _mapY; z++) {
                    if (!_hudMode->activated()) {
                        DrawMesh(_floorMesh, _floorMaterial, MatrixTranslate(x * _gridSize, 0.0f, z * _gridSize));
                        continue;
                    }
                    raylib::RayCollision meshHit = ray.GetCollision(_floorMesh, MatrixTranslate(x * _gridSize, 0.0f, z * _gridSize));
                    if (meshHit.hit) {
                        _hudMode->getTile() = std::make_unique<Tile>(world.getTiles()[x][z]);
                        DrawMesh(_floorMesh, _hitGridMaterial, MatrixTranslate(x * _gridSize, 0.0f, z * _gridSize));
                    } else {
                        DrawMesh(_floorMesh, _floorMaterial, MatrixTranslate(x * _gridSize, 0.0f, z * _gridSize));
                    }
                }
            }

            drawTiles(world.getTiles());

            for (auto &player : _players) {
                if (_hudMode->getTile() != nullptr && _hudMode->getTile()->getX() == player->worldPlayer->getX() && 
                _hudMode->getTile()->getY() == player->worldPlayer->getY())
                    player->draw(_camera);
            }

            for (auto &egg : _eggs) {
                egg->draw(_camera);
            }

            _shader.EndMode();

            // Draw spheres to show where the lights are
            // for (int i = 0; i < MAX_LIGHTS; i++)
            // {
            //     if (_lights[i].enabled) DrawSphereEx(_lights[i].position, 100, 20, 20, _lights[i].color);
            //     else DrawSphereWires(_lights[i].position, 20, 8, 8, ColorAlpha(_lights[i].color, 0.3f));
            // }

            _camera.EndMode();

            Rectangle r = {
                0,
                GUI_HEIGHT - 250,
                GUI_WIDTH,
                250
            };

            // GuiButton(r, "Follow");

            if (_hudMode->activated())
                drawGui(world);
            
            // if (_selectionMode)
            //     GuiWindowBox(r, "Actions");
            // int a = 0;
            // GuiButton((Rectangle) {GUI_WIDTH - 125, GUI_HEIGHT - 200, 100, 60}, "Follow");
            // GuiButton((Rectangle) {GUI_WIDTH - 250, GUI_HEIGHT - 120, 225, 60}, "Kill");
            // GuiButton((Rectangle) {GUI_WIDTH - 250, GUI_HEIGHT - 200, 100, 60}, "Inventaire");
            // GuiDropdownBox((Rectangle) {GUI_WIDTH - 250, GUI_HEIGHT - 200, 100, 100}, "KO", &a, false);

                // end of 3D scene
            textColor.DrawText(raylib::Vector3(_camera.GetPosition()).ToString(), 50, 50, 25);
            textColor.DrawText(raylib::Vector3(_camera.GetTarget()).ToString(), 50, 80, 25);
            _window.DrawFPS();
        }
        _window.EndDrawing();
    }
}
