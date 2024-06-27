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

            _camera.BeginMode();
            _shader.BeginMode();

            _pantheon->renderArena();
            _pantheon->drawPokemons();
            if (_pantheon->getState() == PantheonState::ENDING)
                _pantheon->renderSteve();

            _shader.EndMode();
            _camera.EndMode();

            _pantheon->renderTeam();
            if (_pantheon->getState() == PantheonState::State::GOTOPOKEMONS) {
                _pantheon->renderGoToPokemons();
            }
            if (_pantheon->getState() == PantheonState::State::SHOWPOKEMONS) {
                _pantheon->renderShowPokemons();
            }
            if (_pantheon->getState() == PantheonState::State::ENDING) {
                _pantheon->renderEnding();
            }

        }
       _window.EndDrawing();
    }
}
