/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** update.cpp
*/

#include "Raylib.hpp"

namespace Zappy {
    void Raylib::update(const World &world)
    {

        _mapX = world._mapX;
        _mapY = world._mapY;
        if (IsKeyDown(KEY_SPACE)) {
            _camera.position.y += 10;
            _camera.target.y += 10;
        }
        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
            _camera.position.y -= 10;
            _camera.target.y -= 10;
        }
        if (IsKeyPressed(KEY_N)) {
            std::cout << "j'active le mode GUI" << std::endl;
            _selectionMode = !_selectionMode;
        }
        if (IsKeyPressed(KEY_P)) {
            std::cout << "jai pressé la touche n" << std::endl;
            if (debugMode->activated()) {
            //     std::cout << "je desac" << std::endl;
                debugMode->desactive(_camera);
            } else {
                debugMode->activate(_camera);
            }
        }

        if (debugMode->activated()) {
            if (IsKeyPressed(KEY_ONE)) {
                debugMode->changeAnimation(0);
            } else if (IsKeyPressed(KEY_TWO)) {
                debugMode->changeAnimation(1);
            } else if (IsKeyPressed(KEY_THREE)) {
                debugMode->changeAnimation(2);
            } else if (IsKeyPressed(KEY_FOUR)) {
                debugMode->changeAnimation(3);
            } else if (IsKeyPressed(KEY_FIVE)) {
                debugMode->changeAnimation(4);
            } else if (IsKeyPressed(KEY_SIX)) {
                debugMode->changeAnimation(5);
            } else if (IsKeyPressed(KEY_SEVEN)) {
                debugMode->changeAnimation(6);
            } else if (IsKeyPressed(KEY_EIGHT)) {
                debugMode->changeAnimation(7);
            } else if (IsKeyPressed(KEY_NINE)) {
                debugMode->changeAnimation(8);
            }else if (IsKeyPressed(KEY_ZERO)) {
                debugMode->switchShiny();
            } else if (IsKeyPressed(KEY_I)) {
                debugMode->changeAnimation(false);
            } else if (IsKeyPressed(KEY_K)) {
                debugMode->changeAnimation(true);
            } else if (IsKeyPressed(KEY_J)) {
                debugMode->lastModel();
            } else if (IsKeyPressed(KEY_L))
                debugMode->nextModel();
        }

        _camera.Update(CAMERA_FIRST_PERSON);

        // Update the shader with the camera view vector (points towards { 0.0f, 0.0f, 0.0f })
        float cameraPos[3] = { _camera.position.x, _camera.position.y, _camera.position.z };
        SetShaderValue(_shader, _shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);

        // Check key inputs to enable/disable lights
        if (IsKeyPressed(KEY_Y)) { _lights[0].enabled = !_lights[0].enabled; }
        if (IsKeyPressed(KEY_R)) { _lights[1].enabled = !_lights[1].enabled; }
        if (IsKeyPressed(KEY_G)) { _lights[2].enabled = !_lights[2].enabled; }
        if (IsKeyPressed(KEY_B)) { _lights[3].enabled = !_lights[3].enabled; }

        // Sun & Moon
        size_t revolution = 1789 / 10;
        for (int i = 0; i < 2; i++) {
            _lights[i].position = getSunPosition(GetTime() + revolution / (1 + i), revolution);
            raylib::Color newColor = i == 0 ? SUN_COLOR : MOON_COLOR;
            _lights[i].color =  newColor.Brightness(_lights[i].position.y * 1.f / 1000.f - (i == 0 ? 0.6f : 0.8f));
            // if (_lights[i].position.y <= 20) _lights[i].enabled = false;
            // else _lights[i].enabled = true;
            UpdateLightValues(_shader, _lights[i]);
        }

        if (!_players.empty() && !_players[0]->isDying()) {
            // _camera.target = _players[0]->getPosition() * _gridSize;
            // _camera.position = _players[0]->getPosition() * _gridSize + Vector3{-50, 50, 100};
        }
        updatePlayers(world);
        updateEggs(world);
        testEvolution();
    }

    void Raylib::updatePlayers(const World &world) {
         for (const auto &player : world.getPlayers()) {
            if (!containsPlayer(player)) {
                PokemonInfo pokemon = getPokemon(player.get()->getTeam().getName());
                pokemon.shiny = Utils::random(0, 20) == 6;
                // pokemon.shiny = true;
                _players.push_back(std::make_unique<PlayerRaylib>(player, pokemon, _gridSize, _shader));
            }
        }

        // Update & kill graphical players
        size_t decal = 0;
        for (size_t i = 0; i < _players.size(); i++) {
            if (!world.containsPlayer(_players[i - decal]->worldPlayer->getId())) {
                _players[i]->kill();
            }
            _players[i]->update();
            if (_players[i]->getHeight() > 2000) {
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
                    _eggModelAnimations, _gridSize, _shader, raylib::Color::White())); // getTeamColor(egg->getTeam())));
            }
        }
        size_t decal = 0;
        for (size_t i = 0; i < _eggs.size(); i++) {
            if (!world.containsEgg(_eggs[i - decal]->worldEgg->getId())) {
                _eggs[i]->kill();
            }
            _eggs[i]->update();
            if (_eggs[i]->getHeight() > 2000) {
                _eggs.erase(_eggs.begin() + i - decal);
                decal++;
            }
        }
    }
}
