/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** team.cpp
*/

#include "world/World.hpp"

namespace Zappy
{
    TeamType World::determineTeamType(const std::string &teamName)
    {
        if (teamName == "fire")
            return TeamType::FIRE;
        else if (teamName == "grass")
            return TeamType::GRASS;
        else if (teamName == "water")
            return TeamType::WATER;
        else if (teamName == "steel")
            return TeamType::STEEL;
        else if (teamName == "fairy")
            return TeamType::FAIRY;

        std::vector<TeamType> types;
        for (int i = 0; i < TeamType::SIZE; i++) {
            types.push_back(static_cast<TeamType>(i));
        }
        for (auto &team : _teams) {
            types.erase(std::remove(types.begin(), types.end(), team.getType()), types.end());
        }
        return types[rand() % types.size()];
    }

    void World::addTeam(const std::string &teamName)
    {
        if (teamName.empty())
            return;
        for (auto &team : _teams) {
            if (team.getName() == teamName)
                return;
        }
        _teams.push_back(Team(teamName, determineTeamType(teamName)));
    }

    Team &World::getTeam(const std::string &teamName)
    {
        for (auto &team : _teams) {
            if (team.getName() == teamName)
                return team;
        }
        throw std::runtime_error("Team not found");
    }
} // namespace Zappy
