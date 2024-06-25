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
        _hudMode->setTile(nullptr);
        if (debugMode->activated()) {
            renderDebug();
            return;
        }
        _window.BeginDrawing();
        {
            _window.ClearBackground(raylib::Color::SkyBlue());

            _camera.BeginMode();
            _shader.BeginMode();

            // _tv.Draw(raylib::Vector3(_mapX / 2 * _gridSize, _gridSize * 2, -(float)(_gridSize * 4)), _gridSize);
            float scale = _mapX * _arenaScale;
            _arena.Draw(raylib::Vector3(
                    getArenaOffset(_mapX, _gridSize),
                    scale * _arenaAltitudeScale,
                    getArenaOffset(_mapY, _gridSize)),
                raylib::Vector3(1, 0, 0), -90, raylib::Vector3(scale, scale, scale));

            _sun.Draw(_lights[0].position, _gridSize * 0.8);
            float moonScale = _gridSize * 2;
            _moon.Draw(_lights[1].position, raylib::Vector3(0.1, 0, -0.3), 30, raylib::Vector3(moonScale, true));

            drawTiles(world.getTiles());

            for (auto &egg : _eggs) {
                egg->draw();
            }
            if (_showPlayers) {
                for (auto &player : _players) {
                    player->draw(_hudMode->activated());
                }
            }

            static raylib::Vector3 menuPos = raylib::Vector3(4.4, 10, -9.5) * _gridSize;
            static float menuScale = _gridSize / 200;

            _shader.EndMode();

            if (_menuIntroGif != nullptr && !_menuIntroGif->isAnimEnded())
                _menuIntroGif->draw(_camera, menuPos, menuScale);
            else if (_menuGif != nullptr)
                _menuGif->draw(_camera, menuPos, menuScale);

            // Draw spheres to show where the lights are
            // for (int i = 0; i < MAX_LIGHTS; i++)
            // {
            //     if (_lights[i].enabled) DrawSphereEx(_lights[i].position, 100, 20, 20, _lights[i].color);
            //     else DrawSphereWires(_lights[i].position, 20, 8, 8, ColorAlpha(_lights[i].color, 0.3f));
            // }
            _discardTranspShader.BeginMode();
            for (auto &player : _players) {
                player->drawGifs(_camera);
            }
            if (_hudMode->getTargetedPlayer() != nullptr) {
                _hudMode->getTargetedPlayer()->drawFollowGif(_camera);
            }
            _discardTranspShader.EndMode();

            _camera.EndMode();

            // Rectangle r = {
            //     0,
            //     GUI_HEIGHT - 250,
            //     GUI_WIDTH,
            //     250
            // };

            // GuiButton(r, "Follow");
            if (_menuState == Menu::MENU) {
                drawMenu();
            } else if (_menuState == Menu::NONE) {
            if (_hudMode->activated()) {
                drawHud(world);

                // if (_selectionMode)
                //     GuiWindowBox(r, "Actions");
                // int a = 0;
                // GuiButton((Rectangle) {GUI_WIDTH - 125, GUI_HEIGHT - 200, 100, 60}, "Follow");
                // GuiButton((Rectangle) {GUI_WIDTH - 250, GUI_HEIGHT - 120, 225, 60}, "Kill");
                // GuiButton((Rectangle) {GUI_WIDTH - 250, GUI_HEIGHT - 200, 100, 60}, "Inventaire");
                // GuiDropdownBox((Rectangle) {GUI_WIDTH - 250, GUI_HEIGHT - 200, 100, 100}, "KO", &a, false);

                raylib::Color(0, 0, 0, 160).DrawRectangle(1840, 358, 77, 22);
                _window.DrawFPS(1842, 360);
            } else {
                raylib::Color::Black().DrawText("Appuyez sur N pour activer le mode Détails", 1240, GUI_HEIGHT - 35, 30);
            }
        }
        }
        _window.EndDrawing();
    }
}
