/*
** EPITECH PROJECT, 2023
** gui
** File description:
** state.cpp
*/

#include "Pantheon.hpp"

namespace Zappy {
    void Pantheon::activate(std::string team, std::vector<std::shared_ptr<PlayerRaylib>> players) { 
        setTeam(team);
        getPantheonPlayers(players);
        _state = PantheonState::START;
        _theme.Play();
        _animClock = std::chrono::steady_clock::now();
    }

    void Pantheon::desactivate() {
        _state = PantheonState::NONE;
        _theme.Stop();
        _players.clear();
        _team.clear();
    }
}