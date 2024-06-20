/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Utils.cpp
*/

#include "Raylib.hpp"
#include <cmath>

namespace Zappy
{
    bool Raylib::containsPlayer(std::shared_ptr<Player> player)
    {
        for (const auto &playerRaylib : _players)
        {
            if (playerRaylib->worldPlayer == player)
            {
                return true;
            }
        }
        return false;
    }

    bool Raylib::containsEgg(std::shared_ptr<Egg> egg)
    {
        for (const auto &eggRaylib : _eggs)
        {
            if (eggRaylib->worldEgg == egg)
            {
                return true;
            }
        }
        return false;
    }

    bool Raylib::isOpen()
    {
        return (!_window.ShouldClose());
    }

    raylib::Color Raylib::getTeamColor(const std::string &teamName)
    {
        // for (const auto &team : listTypes)
        // {
        //     if (team == teamName)
        //     {
        //         return raylib::Color(team["color"][0], team["color"][1], team["color"][2], team["color"][3]);
        //     }
        // }
        // if (teamName == "fire")
        //     return raylib::Color(0, 0, 255, 255);
        // if (teamName == "Team2")
        return raylib::Color::White();
    }

    raylib::Color Raylib::getTeamColor(const Team &team)
    {
        return getTeamColor(team.getName());
    }

    raylib::Vector3 Raylib::getSunPosition(double elapsedTime, double cycle_duration_sec)
    {
        const double HALF_CYCLE = cycle_duration_sec / 2.0;
        const double SUN_PEAK_HEIGHT = 1000.0;
        const double SUN_PEAK_WIDTH = 5000.0;

        double timeInCycle = fmod(elapsedTime, cycle_duration_sec);

        double angle = (timeInCycle / cycle_duration_sec) * 2.0 * PI;
        raylib::Vector3 sunPosition;
        // sunPosition.x = SUN_PEAK_WIDTH * (timeInCycle / cycle_duration_sec) - SUN_PEAK_WIDTH / 2;
        sunPosition.y = SUN_PEAK_HEIGHT * sin(angle);
        sunPosition.z = 0.0;
        if (timeInCycle < HALF_CYCLE) {
            sunPosition.x = -SUN_PEAK_WIDTH / 2 + (SUN_PEAK_WIDTH * (timeInCycle / HALF_CYCLE)) + _mapX * _gridSize / 2;
        } else {
            sunPosition.x = SUN_PEAK_WIDTH / 2 - (SUN_PEAK_WIDTH * ((timeInCycle - HALF_CYCLE) / HALF_CYCLE)) + _mapX * _gridSize / 2;
        }
        return sunPosition;
    }
}
