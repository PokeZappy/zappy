/*
** EPITECH PROJECT, 2023
** gui
** File description:
** state.cpp
*/

#include "Pantheon.hpp"
#include "Raylib.hpp"

namespace Zappy {
    void Pantheon::activate(raylib::Camera &camera, std::string team, std::vector<std::shared_ptr<PlayerRaylib>> players) { 
        setTeam(team);
        _teamColor = _raylib.getTeamColor(_team);
        getPantheonPlayers(players);
        _state = PantheonState::START;
        _theme.Play();
        camera.position = _startPos;
        camera.target = _startTarget;
        _animClock = std::chrono::steady_clock::now();

        std::vector<std::string> &types = _raylib.getTypes();

        _endingPosition = raylib::Vector3(-0.2 * (_players.size()), 0.3, 0.2 * (_players.size() / 2));
        _endingTarget = raylib::Vector3(0.3, 0.03, 0.2 * (_players.size() / 2));
        _stevePos = raylib::Vector3(0.23, 0, (0.2 * (_players.size() - 1)) / 2);
    
    }

    void Pantheon::desactivate() {
        _state = PantheonState::NONE;
        _theme.Stop();
        _players.clear();
        _team.clear();
    }
}