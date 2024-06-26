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
        if (_window.ShouldClose())
            return;
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

            _tv.Draw(
                raylib::Vector3(_mapX / 2. - 1 / 2., 0.3, _mapY + 3) * _gridSize,
                raylib::Vector3(0, 1, 0), 180, raylib::Vector3(_gridSize * 6 * (_mapX + _mapY) / 20, true));
            float scale = _mapX * _arenaScale;
            _arena.Draw(raylib::Vector3(
                    getArenaOffset(_mapX, _gridSize),
                    scale * _arenaAltitudeScale,
                    getArenaOffset(_mapY, _gridSize)), scale);

            _sun.Draw(_lights[0].position, raylib::Vector3(1, 0, 0), 180,
                raylib::Vector3(_gridSize * 0.8, true));
            _moon.Draw(_lights[1].position, raylib::Vector3(0.1, 0, -0.3), 30,
                raylib::Vector3(_gridSize * 2, true));

            drawTiles(world.getTiles());

            for (auto &egg : _eggs) {
                egg->draw();
            }
            if (_showPlayers) {
                for (auto &player : _players) {
                    player->draw(_hudMode->activated());
                }
            }

            _shader.EndMode();

            // static raylib::Vector3 menuPos = raylib::Vector3(4.4, 10, -9.5) * _gridSize;
            // static float menuScale = _gridSize / 200;
            // static raylib::Vector3 menuPos = raylib::Vector3(4.5, 4.9, 15.7) * _gridSize;
            raylib::Vector3 menuPos = raylib::Vector3(
                _mapX / 2. - 1 / 2.,
                0.2 + (_mapX + _mapY) / 10.0,
                _mapY * 1.28 + 2.8) * _gridSize;
            float menuScale = _gridSize / 370 * (_mapX + _mapY) / 20;
            raylib::Vector3 menuAngle = raylib::Vector3(PI / 1.485, 0, PI);

            raylib::Vector3 fixedMenuPos = raylib::Vector3(0, 20, 10) * _gridSize;
            float fixedMenuScale = _gridSize / 200;
            raylib::Vector3 fixedMenuAngle = raylib::Vector3(PI / 2, 0, PI);
            if (_menuIntroGif != nullptr && !_menuIntroGif->isAnimEnded()) {
                _menuIntroGif->draw(_camera, menuPos, menuScale, menuAngle);
                if (_menuState != Menu::NONE)
                    _menuIntroGif->draw(_camera, fixedMenuPos, fixedMenuScale, fixedMenuAngle);
            }
            else if (_menuGif != nullptr) {
                _menuGif->draw(_camera, menuPos, menuScale, menuAngle);
                if (_menuState != Menu::NONE)
                    _menuGif->draw(_camera, fixedMenuPos, fixedMenuScale, fixedMenuAngle);
            }

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

            raylib::Color::Black().DrawText(raylib::Vector3(_camera.position), 20, 40, 25);
            raylib::Color::Black().DrawText(raylib::Vector3(_camera.target), 20, 70, 25);
            raylib::Color::Black().DrawText(std::to_string(_mapX) + " " + std::to_string(_mapY), 20, 100, 40);

            if (_menuState == Menu::MENU) {
                drawMenu();
            } else if (_menuState == Menu::NONE) {
                if (_hudMode->activated()) {
                    drawHud(world);
                    raylib::Color(0, 0, 0, 160).DrawRectangle(1840, 358, 77, 22);
                    _window.DrawFPS(1842, 360);
                } else {
                    raylib::Color::Black().DrawText("Appuyez sur N pour activer le mode Détails", 1240, GUI_HEIGHT - 35, 30);
                }
            }
            _escapeMenu->draw();
        }
        _window.EndDrawing();
    }
}
