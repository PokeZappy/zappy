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

namespace Zappy {

    #define TYPES_TEXTURE_PATH "textures/hud/types.png"

    namespace PantheonState {
        enum State {
            START,
            SHOWPOKEMONS,
            ENDING,
            NONE
        };
    }

    class PlayerRaylib;

    class Pantheon {
        public:
            Pantheon(std::string assetsRoot, raylib::Window &_window, raylib::Camera &_camera, raylib::Shader &_shader);
            void setTeam(std::string team) { _team = team;}
            std::string getTeam() { return (_team); }
            PantheonState::State getState() { return (_state); }
            bool activated() { return _state != PantheonState::NONE; }
            void activate(std::string team, std::vector<std::shared_ptr<PlayerRaylib>> players);
            void desactivate();
            void render();
            void renderStart();
            void getPantheonPlayers(std::vector<std::shared_ptr<PlayerRaylib>> players);
        private:
            PantheonState::State _state = PantheonState::NONE;
            std::string _team;
            std::vector<std::shared_ptr<PlayerRaylib>> _players;
            int _minPantheonLevel = 8;

            // Music
            raylib::Music _theme;

            // Textures
            raylib::Texture2D _typesTexture;

            // Assets root
            std::string _assetsRoot;

            // Clocks
            std::chrono::time_point<std::chrono::steady_clock> _animClock;

            // Raylib utils
            raylib::Window &_window;
            raylib::Camera &_camera;
            raylib::Shader &_shader;
    };
}