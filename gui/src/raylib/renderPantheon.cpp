/*
** EPITECH PROJECT, 2023
** gui
** File description:
** renderPantheon.cpp
*/

#include "Raylib.hpp"

namespace Zappy {
    void Raylib::renderPantheon() {
        _window.BeginDrawing();
        {
            _window.ClearBackground(raylib::Color::Black());
            _window.DrawFPS();


            _camera.BeginMode();
            _camera.BeginMode();

            _pantheon->drawPokemons();


            _camera.EndMode();
            _camera.EndMode();

            raylib::Color::White().DrawText("camera pos : " + std::to_string(_camera.position.x) + " " + std::to_string(_camera.position.y) + " " + std::to_string(_camera.position.z), 10, 10, 15);
            raylib::Color::White().DrawText("target pos : " + std::to_string(_camera.target.x) + " " + std::to_string(_camera.target.y) + " " + std::to_string(_camera.target.z), 10, 100, 15);

            if (_pantheon->getState() == PantheonState::State::START) {
                _pantheon->renderStart();
            }
            if (_pantheon->getState() == PantheonState::State::GOTOPOKEMONS) {
                _pantheon->renderGoToPokemons();
            }
            if (_pantheon->getState() == PantheonState::State::SHOWPOKEMONS) {
                _pantheon->renderShowPokemons();
            }

        }
       _window.EndDrawing();
    }
}