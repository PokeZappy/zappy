/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Pantheon.hpp
*/

#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "raylib-cpp.hpp"
#include <chrono>
#include "IGraphicalModule.hpp"

namespace Zappy {

    #define TYPES_TEXTURE_PATH "textures/hud/types.png"

    namespace PantheonState {
        enum State {
            START,
            GOTOPOKEMONS,
            SHOWPOKEMONS,
            ENDING,
            NONE
        };
    }

    class PlayerRaylib;

    class Pantheon {
        public:
            Pantheon(std::string assetsRoot, float gridSize, Camera &_camera);
            void setTeam(std::string team) { _team = team;}
            std::string getTeam() { return (_team); }
            PantheonState::State getState() { return (_state); }
            raylib::Color getTeamColor() { return (_teamColor); }
            bool activated() { return _state != PantheonState::NONE; }
            void activate(std::string team, raylib::Color teamColor,
                std::vector<std::shared_ptr<PlayerRaylib>> players);
            void desactivate();
            void render() {};
            void renderTeam();
            void renderGoToPokemons();
            void renderShowPokemons();
            void renderEnding();
            void renderSteve();
            void renderArena();
            void drawPokemons();
            void drawBravoo();
            void getPantheonPlayers(std::vector<std::shared_ptr<PlayerRaylib>> players);
        private:
            PantheonState::State _state = PantheonState::NONE;
            std::vector<std::shared_ptr<PlayerRaylib>> _players;
            size_t _minPantheonLevel = 1;

            // Team
            std::string _team;
            raylib::Color _teamColor;

            // Music
            raylib::Music _theme;

            // Assets root
            std::string _assetsRoot;

            float _gridSize;
            Camera &_camera;

            // Textures
            raylib::Texture2D _typesTexture;

            // Clocks
            std::chrono::time_point<std::chrono::steady_clock> _animClock;

            // Start animation
            raylib::Vector2 _endTextPos = raylib::Vector2(200, 10);
            raylib::Vector2 _startTextPos = raylib::Vector2(200, GUI_HEIGHT / 2 - 100);
            float _startDuration = 3.0f;
            // float _startDuration = 0.5f;

            // Go to the pokemon
            float _goToPokemonDuration = 1.5f;

            // Start positions of the camera
            raylib::Vector3 _startPos;
            raylib::Vector3 _startTarget;

            // Final position to go to show all the pokemons
            raylib::Vector3 _finalShowPosition;
            raylib::Vector3 _finalShowTarget;

            // Index of the current pokemon we're showing
            size_t _currentShowIndex = 0;
            raylib::Vector3 _currentShowPosition;
            raylib::Vector3 _currentShowTarget;

            float _pokemonSpacing = _gridSize * 4;

            // Duration of the pokemons animations
            float _showPokemonDuration = 4.0f;
            // float _showPokemonDuration = 0.5f;
            float _transitionPokemonDuration = 1.5f;
            // float _transitionPokemonDuration = 0.5f;

            int _maxPokemonPerTeam = 6;

            float _endingDuration = 4.0f;
            raylib::Vector3 _endingPosition;
            raylib::Vector3 _endingTarget;

            // Steve
            raylib::Model _steve;
            std::vector<raylib::ModelAnimation> _steveAnims;
            raylib::Vector3 _stevePos;
            int _frame = 0;

            // Arena
            raylib::Model _arena;
            raylib::Vector3 _arenaPos;
    };
}
