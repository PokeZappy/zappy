/*
** EPITECH PROJECT, 2023
** gui
** File description:
** render.cpp
*/

#include "Pantheon.hpp"
#include "PlayerRaylib.hpp"
#include "UtilsRaylib.hpp"

namespace Zappy {

    void Pantheon::drawBravoo() {
        raylib::Color _teamColorWithAlpha = _teamColor;
        _teamColorWithAlpha.a = 90;
        std::string pkName = _players[_currentShowIndex]->infos.displayName;
        std::string pkLvl = "N." + std::to_string(_players[_currentShowIndex]->worldPlayer->getLevel());
        _teamColorWithAlpha.DrawRectangle(raylib::Vector2(0, 100), raylib::Vector2(GUI_WIDTH, 100));
        _teamColorWithAlpha.DrawRectangle(raylib::Vector2(0, GUI_HEIGHT - 200), raylib::Vector2(GUI_WIDTH, 100));
        raylib::Color::White().DrawText("Bravo !!!!", 40, 120, 60);
        raylib::Color::White().DrawText(pkName, GUI_WIDTH - 40 - MeasureText(pkName.c_str(), 40), GUI_HEIGHT - 100 - 80, 40);
        raylib::Color::White().DrawText(pkLvl, GUI_WIDTH - 40 - MeasureText(pkName.c_str(), 40), GUI_HEIGHT - 100 - 40, 40);
    }

    void Pantheon::renderSteve() {
        _steve.UpdateAnimation(_steveAnims[5], _frame);
        _frame++;
        _steve.Draw(_stevePos,
        raylib::Vector3(0, 1, 0), 90,
        raylib::Vector3(_gridSize / 4, true));
    }

    void Pantheon::renderArena() {
        _arena.Draw(_arenaPos,
        raylib::Vector3(0, 1, 0), 90,
        raylib::Vector3(_gridSize * 6, true));
    }

    void Pantheon::drawPokemons() {
        for (size_t i = 0; i < _players.size(); i++) {
            _players[i]->drawPantheon(raylib::Vector3(-_gridSize * 2, -_gridSize * 1.8, -_gridSize * 5 + i * _pokemonSpacing));
        }
    }

    void Pantheon::renderShowPokemons() {
        std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - _animClock;

        if (elapsed_seconds.count() > _showPokemonDuration) {

            if (_currentShowIndex == _players.size() - 1) {
                _animClock = std::chrono::steady_clock::now();
                _state = PantheonState::ENDING;
                return;
            }

            raylib::Vector3 _nextPosition = raylib::Vector3(_currentShowPosition.x, _currentShowPosition.y, _currentShowPosition.z + _pokemonSpacing);
            raylib::Vector3 _nextTarget = raylib::Vector3(_currentShowTarget.x, _currentShowTarget.y, _currentShowTarget.z + _pokemonSpacing);

            float moveFactor = (elapsed_seconds.count() - _showPokemonDuration) / _transitionPokemonDuration;

            if (moveFactor > 1.0f)
                moveFactor = 1.0f;
            raylib::Vector3 cameraPos = _currentShowPosition + (_nextPosition - _currentShowPosition) * moveFactor;
            raylib::Vector3 cameraTarget = _currentShowTarget + (_nextTarget - _currentShowTarget) * moveFactor;
            _camera.position = cameraPos;
            _camera.target = cameraTarget;
            if (elapsed_seconds.count() > _showPokemonDuration + _transitionPokemonDuration) {
                _currentShowIndex++;
                _currentShowPosition = _nextPosition;
                _currentShowTarget = _nextTarget;
                _animClock = std::chrono::steady_clock::now();
            }
        } else {
            drawBravoo();
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
        _camera.position = cameraPos;
        _camera.target = cameraTarget;
    }

    void Pantheon::renderTeam() {
        raylib::Rectangle srcType = UtilsRaylib::getTypeRectangle(_team);
        std::string text = "Félicitations à l'équipe ";
        raylib::Vector2 textPos = _endTextPos;

        if (_state == PantheonState::START) {
            std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - _animClock;
            float moveFactor = elapsed_seconds.count() / _startDuration;

            if (moveFactor > 1.0f)
                moveFactor = 1.0f;
            textPos = _startTextPos + (_endTextPos - _startTextPos) * moveFactor;
            if (elapsed_seconds.count() > _startDuration) {
                if (elapsed_seconds.count() > _startDuration + 2) {
                    _animClock = std::chrono::steady_clock::now();
                    _state = PantheonState::State::GOTOPOKEMONS;
                }
                    // _menuState = Menu::NONE;
            }
        }
        if (srcType.x == -1) {
            text += _team + " !";
        } else {
            _typesTexture.Draw(srcType, raylib::Rectangle(textPos.x + MeasureText("Félicitations à l'équipe", 100) + 50, textPos.y, 200, 100));
        }
        _teamColor.DrawText(text, textPos.x, textPos.y, 100);

    }

    void Pantheon::renderEnding() {
            std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - _animClock;
            float moveFactor = elapsed_seconds.count() / _startDuration;

            if (moveFactor > 1.0f)
                moveFactor = 1.0f;

            if (elapsed_seconds.count() < _endingDuration) {
                raylib::Vector3 cameraPos = _currentShowPosition + (_endingPosition - _currentShowPosition) * moveFactor;
                raylib::Vector3 cameraTarget = _currentShowTarget + (_endingTarget - _currentShowTarget) * moveFactor;
                _camera.position = cameraPos;
                _camera.target = cameraTarget;
            }
    }
}
