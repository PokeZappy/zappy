/*
** EPITECH PROJECT, 2023
** gui
** File description:
** render.cpp
*/

#include "Pantheon.hpp"

namespace Zappy {

    void Pantheon::renderStart() {
        
    }

    void Pantheon::render() {
        _window.BeginDrawing();
        {
            _window.ClearBackground(raylib::Color::Black());
            _window.DrawFPS();


            _camera.BeginMode();
            _shader.BeginMode();

            if (_state == PantheonState::START) {
                renderStart();
            }

            _shader.EndMode();
            _camera.EndMode();

        }
        _window.EndDrawing();
    }
}