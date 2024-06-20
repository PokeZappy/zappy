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
        if (debugMode->getType() != CHAT) {
             if (IsKeyDown(KEY_SPACE)) {
            _camera.position.y += 1;
            _camera.target.y += 1;
            }
            if (IsKeyDown(KEY_LEFT_SHIFT))
            {
                _camera.position.y -= 1;
                _camera.target.y -= 1;
            }
        }
        if (IsKeyPressed(KEY_N)) {
            _selectionMode = !_selectionMode;
        }
        if (IsKeyPressed(KEY_P)) {
            if (debugMode->activated() && debugMode->getType() == NONE) {
            //     std::cout << "je desac" << std::endl;
                debugMode->desactive(_camera);
            } else {
                debugMode->activate(_camera);
            }
        }
        if (debugMode->activated()) {
            debugMode->update();
        }

        if (debugMode->getType() != CHAT)
            _camera.Update(CAMERA_FIRST_PERSON);

        // Update the shader with the camera view vector (points towards { 0.0f, 0.0f, 0.0f })
        float cameraPos[3] = { _camera.position.x, _camera.position.y, _camera.position.z };
        SetShaderValue(_shader, _shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);

        // Check key inputs to enable/disable lights
        if (IsKeyPressed(KEY_Y)) { _lights[0].enabled = !_lights[0].enabled; }
        if (IsKeyPressed(KEY_R)) { _lights[1].enabled = !_lights[1].enabled; }
        if (IsKeyPressed(KEY_G)) { _lights[2].enabled = !_lights[2].enabled; }
        if (IsKeyPressed(KEY_B)) { _lights[3].enabled = !_lights[3].enabled; }

        _lights[0].position.y += sinf(GetTime()) * 5 - 0.01;
        for (int i = 0; i < MAX_LIGHTS; i++) UpdateLightValues(_shader, _lights[i]);

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
         for (const auto &egg : world.getEggs()) {
            if (!containsEgg(egg)) {
                _eggs.push_back(std::make_unique<EggRaylib>(egg, _eggModel,
                    _eggModelAnimations, _gridSize, _shader));
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
