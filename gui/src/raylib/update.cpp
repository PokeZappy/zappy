/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** update.cpp
*/

#include "Raylib.hpp"
#include <chrono>

namespace Zappy {
    void Raylib::update(const World &world)
    {
        _hudMode->clearPlayers();
        if (_menuState != Menu::NONE) {
            updateMenu();
        }

        if (_escapeMenu->activated()) {
            _escapeMenu->update(*this);
        }

        handleKeys();

        if (!_pantheon->activated() && !world.getWinningTeam().empty())
            _pantheon->activate(world.getWinningTeam(), getTeamColor(world.getWinningTeam()), _players);

        if (debugMode->getType() != CHAT && (!_hudMode->isChatEnabled()) && _menuState == Menu::NONE && !_escapeMenu->activated())
            _camera.Update(_cameraViewMode);

        // Sun & Moon
        size_t revolution = 1789 / 10;
        auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) / 1000.;
        for (int i = 0; i < 2; i++) {
            _lights[i].position = getSunPosition(currentTime.count() + revolution / (1 + i), revolution);
            raylib::Color newColor = i == 0 ? SUN_COLOR : MOON_COLOR;
            float brightness = _lights[i].position.y / _gridSize / 50;
            _lights[i].color =  newColor.Brightness(brightness * (i == 0 ? 1.0f : 0.3f));
            UpdateLightValues(_shader, _lights[i]);
        }
        if (_showPlayers)
            updatePlayers(world);
        updateEggs(world);
        testEvolution();

        for (auto &player : _players) {
                if ((_hudMode->getTile() != nullptr) &&
                (_hudMode->getTile()->getY() == player->worldPlayer->getX()) &&
                (_hudMode->getTile()->getX() == player->worldPlayer->getY()))
                    _hudMode->addPlayer(player);
        }

        if (_hudMode->activated() && _hudMode->getTile() != nullptr && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            _hudMode->applySelectedPlayerToTarget();

        if (_hudMode->activated()) {
            _cameraViewMode = _hudMode->followTarget(_camera);
            _hudMode->update(_socket);
        }

        float wheel = GetMouseWheelMove();
        if (wheel > 0 && _hudMode->activated()) {
            _hudMode->scrollUp(wheel);
        } else if (wheel < 0 && _hudMode->activated()) {
            _hudMode->scrollDown(wheel);
        }


        for (auto &model : _models) {
            model.second->update();
        }
        _mainTheme.Update();
        _pantheonTheme.Update();
        if (_menuIntroGif != nullptr && !_menuIntroGif->isAnimEnded()) {
            _menuIntroGif->update();
        }
        else if (_menuGif != nullptr)
            _menuGif->update();

        if (_menuIntroGif != nullptr && _menuIntroGif->isAnimEnded())
            _menuIntroGif.release();
    }

    void Raylib::updatePlayers(const World &world) {
         for (const auto &player : world.getPlayers()) {
            if (!containsPlayer(player)) {
                PokemonInfo pokemon = getPokemon(player.get()->getTeam().getName());
                pokemon.shiny = Utils::random(0, 20) == 6;


                // add the model if the pokemon doesn't exist in the map
                if (_models.count(pokemon.id) <= 0) {
                    _models[pokemon.id] = std::make_shared<RaylibModels>(_assetsRoot, pokemon.id, pokemon.animPantheon, _shader);
                }

                _players.push_back(std::make_unique<PlayerRaylib>(player,
                    pokemon, _models[pokemon.id], _gridSize, getTeamColor(player->getTeam()),
                    _broadcastGif, _successGif, _failureGif, _followGif, _pushGif));
            }
        }

        // Update & kill graphical players
        size_t decal = 0;
        for (size_t i = 0; i < _players.size(); i++) {
            if (!world.containsPlayer(_players[i - decal]->worldPlayer->getId())) {
                _players[i]->kill();
            }
            _players[i]->update();
            if (_players[i]->getHeight() > _gridSize * 100) {
                _players.erase(_players.begin() + i - decal);
                decal++;
            }
        }
    }

    void Raylib::updateEggs(const World &world) {
        _eggModel.UpdateAnimation(_eggModelAnimations[0], _eggAnimFrame);
        _eggAnimFrame++;
         for (const auto &egg : world.getEggs()) {
            if (!containsEgg(egg)) {
                _eggs.push_back(std::make_unique<EggRaylib>(egg, _eggModel,
                    _eggModelAnimations, _gridSize, _shader, getTeamColor(egg->getTeam())));
            }
        }
        size_t decal = 0;
        for (size_t i = 0; i < _eggs.size(); i++) {
            if (!world.containsEgg(_eggs[i - decal]->worldEgg->getId())) {
                _eggs[i]->kill();
            }
            _eggs[i]->update();
            if (_eggs[i]->getAnimatedScale() < 0) {
                _eggs.erase(_eggs.begin() + i - decal);
                decal++;
            }
        }
    }

    void Raylib::updateMenu() {
        std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - _menuClock;

        if (_menuState == Menu::STARTING) {
            _camera.position = getStartPos();
            _camera.target = getStartTarget();
            if (!_forceStartAnimation) {
                if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) ||
            IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D))
                _menuState = Menu::NONE;
            }
            if (elapsed_seconds.count() >= _startTime) {
                _menuClock = std::chrono::steady_clock::now();
                _menuState = Menu::MENU;
            }
        }

        if (_menuState == Menu::ENDING) {
            float moveFactor = elapsed_seconds.count() / _durationEnding;

            if (moveFactor > 1.0f)
                moveFactor = 1.0f;
            _camera.position = getStartPos() + (_endPos - getStartPos()) * moveFactor;
            _camera.target = getStartTarget() + (_endTarget - getStartTarget()) * moveFactor;
            if (elapsed_seconds.count() > _durationEnding) {
                _menuClock = std::chrono::steady_clock::now();
                _menuState = Menu::NONE;
            }
        }

        if (_menuState == Menu::MENU) {
             if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) ||
            IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D))
                _menuState = Menu::NONE;
            if (IsKeyPressed(KEY_ENTER)) {
                _menuClock = std::chrono::steady_clock::now();
                _endTarget = raylib::Vector3(_mapX / 2., 0.5, 5) * _gridSize;
                _endPos = raylib::Vector3(_mapX / 2., 2, -5) * _gridSize;
                _menuState = Menu::ENDING;
            }
        }
    }
}
