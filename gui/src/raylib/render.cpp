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
        _hudMode->setTile(nullptr);
        _hudMode->clearPlayers();
        if (debugMode->activated()) {
            renderDebug();
            return;
        }
        raylib::Color textColor = raylib::Color::Black();
        _window.BeginDrawing();
        {
            _window.ClearBackground(raylib::Color::SkyBlue());

            _camera.BeginMode();
            _shader.BeginMode();

            _tv.Draw(raylib::Vector3(_mapX / 2 * _gridSize - 50, 80, -(float)(_gridSize * 4)), 2000);
            float scale = _mapX * _arenaScale;
            _arena.Draw(raylib::Vector3(
                    getArenaOffset(_mapX, _gridSize),
                    scale * _arenaAltitudeScale,
                    getArenaOffset(_mapY, _gridSize)),
                raylib::Vector3(1, 0, 0), -90, raylib::Vector3(scale, scale, scale));

            _sun.Draw(_lights[0].position, 10);
            _moon.Draw(_lights[1].position, 20);

            drawTiles(world.getTiles());

            for (auto &player : _players) {
                if ((_hudMode->getTile() != nullptr) &&
                (_hudMode->getTile()->getX() == player->worldPlayer->getX()) &&
                (_hudMode->getTile()->getY() == player->worldPlayer->getY()))
                    _hudMode->addPlayer(player);
                player->draw(_camera, _hudMode->activated());
            }

            for (auto &egg : _eggs) {
                // if ((_hudMode->getTile() != nullptr) &&
                // (_hudMode->getTile()->getX() == egg->worldEgg->getX()) &&
                // (_hudMode->getTile()->getY() == egg->worldEgg->getY()))
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

            raylib::Color::White().Alpha(0.2).DrawRectangle(0, 0, 800, 250);

            textColor.DrawText("Cam Position: " + raylib::Vector3(_camera.GetPosition()).ToString(), 50, 50, 25);
            textColor.DrawText("Cam Target: " + raylib::Vector3(_camera.GetTarget()).ToString(), 50, 80, 25);
            textColor.DrawText("Cam Up: " + raylib::Vector3(_camera.GetUp()).ToString(), 50, 110, 25);
            textColor.DrawText("Player count (Graphical): " + std::to_string(_players.size()), 50, 140, 25);
            textColor.DrawText("Player count (World): " + std::to_string(world.getPlayers().size()), 50, 170, 25);
            textColor.DrawText("Egg count (Graphical): " + std::to_string(_eggs.size()), 50, 200, 25);
            textColor.DrawText("Egg count (World): " + std::to_string(world.getEggs().size()), 50, 230, 25);
            _window.DrawFPS();
        }
        _window.EndDrawing();
    }
}