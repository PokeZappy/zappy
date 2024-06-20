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
            _window.DrawFPS();
            // 3D scene

            _camera.BeginMode();
            _shader.BeginMode();

            for (int x = 0; x < _mapX; x++)
            {
                for (int z = 0; z < _mapY; z++)
                {
                    if (!_selectionMode)
                    {
                        DrawMesh(_floorMesh, _floorMaterial, MatrixTranslate(x * _gridSize, 0.0f, z * _gridSize));
                        continue;
                    }
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

            for (auto &egg : _eggs)
            {
                egg->draw(_camera);
            }

            _tv.Draw(raylib::Vector3(_mapX / 2 * _gridSize - 50, 80, -(float)(_gridSize * 4)), 2000);

            DrawCube(Vector3Zero(), 2.0, 4.0, 2.0, WHITE);

            _shader.EndMode();

            // Draw spheres to show where the lights are
            for (int i = 0; i < MAX_LIGHTS; i++)
            {
                if (_lights[i].enabled) DrawSphereEx(_lights[i].position, 20, 8, 8, _lights[i].color);
                
                else DrawSphereWires(_lights[i].position, 20, 8, 8, ColorAlpha(_lights[i].color, 0.3f));
            }

            _camera.EndMode();

            Rectangle r = {
                0,
                GUI_HEIGHT - 250,
                GUI_WIDTH,
                250
            };

            // GuiButton(r, "Follow");

            if (_selectionMode)
                GuiWindowBox(r, "Actions");
            int a = 0;
            GuiButton((Rectangle) {GUI_WIDTH - 125, GUI_HEIGHT - 200, 100, 60}, "Follow");
            GuiButton((Rectangle) {GUI_WIDTH - 250, GUI_HEIGHT - 120, 225, 60}, "Kill");
            GuiButton((Rectangle) {GUI_WIDTH - 250, GUI_HEIGHT - 200, 100, 60}, "Inventaire");
            // GuiDropdownBox((Rectangle) {GUI_WIDTH - 250, GUI_HEIGHT - 200, 100, 100}, "KO", &a, false);

                // end of 3D scene
            textColor.DrawText(raylib::Vector3(_camera.GetPosition()).ToString(), 50, 50, 25);
            textColor.DrawText(raylib::Vector3(_camera.GetTarget()).ToString(), 50, 80, 25);
        }
        _window.EndDrawing();
    }
}
