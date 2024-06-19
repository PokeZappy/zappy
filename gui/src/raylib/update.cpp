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
            _camera.position.y += 1;
            _camera.target.y += 1;
        }
        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
            _camera.position.y -= 1;
            _camera.target.y -= 1;
        }

        // Update Graphical Player list
        _camera.Update(CAMERA_FIRST_PERSON);
        if (!_players.empty() && !_players[0]->isDying()) {
            // _camera.target = _players[0]->getPosition() * _gridSize;
            // _camera.position = _players[0]->getPosition() * _gridSize + Vector3{-50, 50, 100};
        }
        for (const auto &player : world.getPlayers()) {
            if (!containsPlayer(player)) {
                PokemonInfo pokemon = getPokemon(player.get()->getTeam().getName());
                pokemon.shiny = Utils::random(0, 20) == 6;
                // pokemon.shiny = true;
                _players.push_back(std::make_unique<PlayerRaylib>(player, pokemon, _gridSize));
            }
        }
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
        testEvolution();
    }
}