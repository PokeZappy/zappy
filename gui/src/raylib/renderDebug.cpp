/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** renderDebug.cpp
*/

#include "Raylib.hpp"

namespace Zappy {
    void Raylib::renderDebug(void) {
        DebugType type = debugMode->getType();
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
            switch (type) {
                case NONE: debugMode->drawPokemon(); break;
                case FRAMESTEPPER: debugMode->drawFrameStepper(); break;
                case CHAT: debugMode->drawPokemon(); debugMode->drawChat(); break;
            }
        }
        _window.EndDrawing();
    }
}
