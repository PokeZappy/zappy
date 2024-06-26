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
    class Raylib;

    class Pantheon {
        public:
            Pantheon(std::string assetsRoot, Raylib &raylib);
            void setTeam(std::string team) { _team = team;}
            std::string getTeam() { return (_team); }
            PantheonState::State getState() { return (_state); }
            raylib::Color getTeamColor() { return (_teamColor); }
            bool activated() { return _state != PantheonState::NONE; }
            void activate(raylib::Camera &camera, std::string team, std::vector<std::shared_ptr<PlayerRaylib>> players);
            void desactivate();
            void render() {};
            void renderTeam();
            void renderGoToPokemons();
            void renderShowPokemons();
            void drawPokemons();
            void drawBravoo();
            void getPantheonPlayers(std::vector<std::shared_ptr<PlayerRaylib>> players);
        private:
            PantheonState::State _state = PantheonState::NONE;
            std::vector<std::shared_ptr<PlayerRaylib>> _players;
            int _minPantheonLevel = 1;

            // Team
            std::string _team;
            raylib::Color _teamColor;

            // Music
            raylib::Music _theme;

            // Textures
            raylib::Texture2D _typesTexture;

            // Assets root
            std::string _assetsRoot;

            // Clocks
            std::chrono::time_point<std::chrono::steady_clock> _animClock;

            // Raylib utils
            Raylib &_raylib;

            // Start animation
            raylib::Vector2 _endTextPos = raylib::Vector2(200, 10);
            raylib::Vector2 _startTextPos = raylib::Vector2(200, GUI_HEIGHT / 2 - 100);
            float _startDuration = 1.0f;

            // Go to the pokemon
            float _goToPokemonDuration = 1.5f;

            // Start positions of the camera
            raylib::Vector3 _startPos = raylib::Vector3(-1.17, 0.57, -1.14);
            raylib::Vector3 _startTarget = raylib::Vector3(-1.15, 0.56, -1.08);

            // Final position to go to show all the pokemons
            raylib::Vector3 _finalShowPosition;
            raylib::Vector3 _finalShowTarget;

            // Index of the current pokemon we're showing
            int _currentShowIndex = 0;
            raylib::Vector3 _currentShowPosition = raylib::Vector3(0.15, 0.05, 0);
            raylib::Vector3 _currentShowTarget = raylib::Vector3(0.22, 0.04, 0);

            // Duration of the pokemons animations
            int _showPokemonDuration = 4.0f;
            int _transitionPokemonDuration = 1.5f;

            int _maxPokemonPerTeam = 6;
    };
}