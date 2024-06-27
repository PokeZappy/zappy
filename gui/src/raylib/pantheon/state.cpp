/*
** EPITECH PROJECT, 2023
** gui
** File description:
** state.cpp
*/

#include "Pantheon.hpp"
#include "Raylib.hpp"

namespace Zappy {
    void Pantheon::activate(std::string team, raylib::Color teamColor,
    std::vector<std::shared_ptr<PlayerRaylib>> players) {
        setTeam(team);
        _teamColor = teamColor;
        getPantheonPlayers(players);
        _state = PantheonState::START;
        _camera.position = _startPos;
        _camera.target = _startTarget;
        _animClock = std::chrono::steady_clock::now();
    }

    void Pantheon::desactivate() {
        _state = PantheonState::NONE;
        _players.clear();
        _team.clear();
    }
}
