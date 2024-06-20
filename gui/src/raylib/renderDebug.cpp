/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** renderDebug.cpp
*/

#include "Raylib.hpp"

namespace Zappy {
    void Raylib::renderDebug(const World &world) {
        raylib::Color textColor = raylib::Color::Black();
        _window.BeginDrawing();
        {
            _window.ClearBackground(raylib::Color::Black());
            _window.DrawFPS();


            _camera.BeginMode();
            _shader.BeginMode();


            debugMode->drawModel();

            _shader.EndMode();
            _camera.EndMode();

            debugMode->drawAnimations();
            debugMode->drawPokemon();
        }
        _window.EndDrawing();
    }
}