/*
** EPITECH PROJECT, 2023
** gui
** File description:
** render.cpp
*/

#include "Pantheon.hpp"
#include "Raylib.hpp"

namespace Zappy {

    void Pantheon::drawPokemons() {
        for (int i = 0; i < _players.size(); i++) {
            _players[i]->drawPantheon(raylib::Vector3(0.3, 0, i * 0.2));
        }
    }

    void Pantheon::renderShowPokemons() {
        std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - _animClock;

        if (elapsed_seconds.count() > _showPokemonDuration) {

            if (_currentShowIndex == _players.size() - 1) {
                _state = PantheonState::ENDING;
                return;
            }

            raylib::Vector3 _nextPosition = raylib::Vector3(_currentShowPosition.x, _currentShowPosition.y, _currentShowPosition.z + 0.2);
            raylib::Vector3 _nextTarget = raylib::Vector3(_currentShowTarget.x, _currentShowTarget.y, _currentShowTarget.z + 0.2);
            
            float moveFactor = (elapsed_seconds.count() - _showPokemonDuration) / _transitionPokemonDuration;

            if (moveFactor > 1.0f)
                moveFactor = 1.0f;
            raylib::Vector3 cameraPos = _currentShowPosition + (_nextPosition - _currentShowPosition) * moveFactor;
            raylib::Vector3 cameraTarget = _currentShowTarget + (_nextTarget - _currentShowTarget) * moveFactor;
            _raylib.getCamera().position = cameraPos;
            _raylib.getCamera().target = cameraTarget;
            if (elapsed_seconds.count() > _showPokemonDuration + _transitionPokemonDuration) {
                _currentShowIndex++;
                _currentShowPosition = _nextPosition;
                _currentShowTarget = _nextTarget;
                _animClock = std::chrono::steady_clock::now();
            }
        }
    }

    void Pantheon::renderGoToPokemons() {
        std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - _animClock;
        float moveFactor = elapsed_seconds.count() / _goToPokemonDuration;

        if (moveFactor > 1.0f)
            moveFactor = 1.0f;

        if (elapsed_seconds.count() > _goToPokemonDuration) {
            _animClock = std::chrono::steady_clock::now();
            _finalShowPosition = raylib::Vector3(_currentShowPosition.x, _currentShowPosition.y, _currentShowPosition.z + 0.2 * (_players.size() - 1) + 0.005);
            _finalShowTarget = raylib::Vector3(_currentShowTarget.x, _currentShowTarget.y, _currentShowTarget.z + 0.2 * (_players.size() - 1) + 0.005);
            std::cout << 0.2 * 2 << std::endl;
            // std::cout << _finalShowPosition.x << " " << _finalShowPosition.y << " " << _finalShowPosition.z << std::endl;
            _state = PantheonState::State::SHOWPOKEMONS;
        }
        raylib::Vector3 cameraPos = _startPos + (_currentShowPosition - _startPos) * moveFactor;
        raylib::Vector3 cameraTarget = _startTarget + (_currentShowTarget - _startTarget) * moveFactor;
        _raylib.getCamera().position = cameraPos;
        _raylib.getCamera().target = cameraTarget;
    }

    void Pantheon::renderStart() {
        std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - _animClock;
        float moveFactor = elapsed_seconds.count() / _startDuration;

        if (moveFactor > 1.0f)
            moveFactor = 1.0f;
        raylib::Vector2 textPos = _startTextPos + (_endTextPos - _startTextPos) * moveFactor;
        if (elapsed_seconds.count() > _startDuration) {
            if (elapsed_seconds.count() > _startDuration + 2) {
                _animClock = std::chrono::steady_clock::now();
                _state = PantheonState::State::GOTOPOKEMONS;
            }
                // _menuState = Menu::NONE;
        }
        raylib::Rectangle srcType = Raylib::getTypeRectangle(_team);
        std::string text = "Félicitations à l'équipe";
        if (srcType.x == -1) {
            text += _team + " !";
        } else {
            _typesTexture.Draw(srcType, raylib::Rectangle(textPos.x + MeasureText("Félicitations à l'équipe", 100) + 50, textPos.y, 200, 100));
        }
        _teamColor.DrawText(text, textPos.x, textPos.y, 100);
    }

    // void Raylib::renderPantheon() {
    //     _window.BeginDrawing();
    //     {
    //         _window.ClearBackground(raylib::Color::Black());
    //         _window.DrawFPS();


    //         _camera.BeginMode();
    //         _camera.BeginMode();

    //         raylib::Color::White().DrawText("salut", 1000, 800, 50);

    //         // if (_state == PantheonState::START) {
    //         //     renderStart();
    //         // }

    //         _camera.EndMode();
    //         _camera.EndMode();

    //     }
    //    _window.EndDrawing();
    // }
}