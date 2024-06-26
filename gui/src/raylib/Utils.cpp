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

    static raylib::Rectangle getTypeRectangle(std::string team) {
        // int width = 28;
        //  if (team == "bug") {
        //     return raylib::Rectangle(0, 14, width, 14);
        // } else if (team == "dark") {
        //     return raylib::Rectangle(0, 28, width, 14);
        // } else if (team == "dragon") {
        //     return  raylib::Rectangle(0, 42, width, 14);
        // } else if (team == "electric") {
        //     return raylib::Rectangle(0, 56, width, 14);
        // } else if (team == "fairy") {
        //     return raylib::Rectangle(0, 70, width, 14);
        // } else if (team == "fight") {
        //     return raylib::Rectangle(0, 84, width, 14);
        // } else if (team == "fire") {
        //     return raylib::Rectangle(0, 98, width, 14);
        // } else if (team == "fly") {
        //     return raylib::Rectangle(0, 112, width, 14);
        // } else if (team == "ghost") {
        //     return raylib::Rectangle(0, 126, width, 14);
        // } else if (team == "grass") {
        //     return raylib::Rectangle(0, 140, width, 14);
        // } else if (team == "ground") {
        //     return raylib::Rectangle(0, 154, width, 14);
        // } else if (team == "ice") {
        //     return raylib::Rectangle(0, 168, width, 14);
        // } else if (team == "normal") {
        //     return raylib::Rectangle(0, 182, width, 14);
        // } else if (team == "poison") {
        //     return raylib::Rectangle(0, 196, width, 14);
        // } else if (team == "psychic") {
        //     return raylib::Rectangle(0, 210, width, 14);
        // } else if (team == "rock") {
        //     return raylib::Rectangle(0, 224, width, 14);
        // } else if (team == "steel") {
        //     return raylib::Rectangle(0, 238, width, 14);
        // } else if (team == "water") {
        //     return raylib::Rectangle(0, 252, width, 14);
        // } else {
        //     return raylib::Rectangle(-1, -1, -1, -1);
        // }
    }

    raylib::Color Raylib::getTeamColor(const std::string &teamName)
    {
        int i = 0;
        for (const auto &team : _listTypes) {
            if (team == teamName) {
                return _listTypesColors[i];
            }
            i++;
        }
        i = 0;
        for (const auto &team : _listTypesCustom) {
            if (team == teamName) {
                return _listTypesColorsCustom[i];
            }
            i++;
        }
        _listTypesCustom.push_back(teamName);
        int min = 20;
        int max = 220;
        raylib::Color newColor(Utils::random(min, max), Utils::random(min, max), Utils::random(min, max));
        _listTypesColorsCustom.push_back(newColor);
        return newColor;
    }

    raylib::Color Raylib::getTeamColor(const Team &team)
    {
        return getTeamColor(team.getName());
    }

    raylib::Vector3 Raylib::getSunPosition(double elapsedTime, double cycle_duration_sec)
    {
        const double HALF_CYCLE = cycle_duration_sec / 2.0;
        const double SUN_PEAK_HEIGHT = 5.0 * _gridSize * _mapX;
        const double SUN_PEAK_WIDTH = 8.0 * _gridSize * _mapY;

        double timeInCycle = fmod(elapsedTime, cycle_duration_sec);

        double angle = (timeInCycle / cycle_duration_sec) * 2.0 * PI;
        raylib::Vector3 sunPosition;
        // sunPosition.x = SUN_PEAK_WIDTH * (timeInCycle / cycle_duration_sec) - SUN_PEAK_WIDTH / 2;
        sunPosition.y = SUN_PEAK_HEIGHT * sin(angle);
        sunPosition.z = - _gridSize * 40.0;
        if (timeInCycle < HALF_CYCLE) {
            sunPosition.x = -SUN_PEAK_WIDTH / 2 + (SUN_PEAK_WIDTH * (timeInCycle / HALF_CYCLE)) + _mapX * _gridSize / 2;
        } else {
            sunPosition.x = SUN_PEAK_WIDTH / 2 - (SUN_PEAK_WIDTH * ((timeInCycle - HALF_CYCLE) / HALF_CYCLE)) + _mapX * _gridSize / 2;
        }
        return sunPosition;
    }

    raylib::Vector3 Raylib::getStartPos(void)
    {
        if (_mapX == 10 && _mapY == 10) {
            if (_isMenuDay)
                return raylib::Vector3(4.42, 3.46, 13.25) * _gridSize;
            return raylib::Vector3(4.41, 3.67, 13.17) * _gridSize;
        }
        if (_mapX == 30 && _mapY == 30)
            return raylib::Vector3(_mapX / 2. - 1 / 2., 5.5 + (_mapX + _mapY) / 15., _mapY + 2) * _gridSize;
        return raylib::Vector3(0, 20, 5) * _gridSize;
        // return raylib::Vector3(
        //     _mapX / 2. - 1 / 2.,
        //     5.5 + (_mapX + _mapY) / 8.,
        //     _mapY * 1.1 + 0.5
        // ) * _gridSize;
    }

    raylib::Vector3 Raylib::getStartTarget(void)
    {
        if (_mapX == 10 && _mapY == 10) {
            if (_isMenuDay)
                return raylib::Vector3(4.40, 1.02, 17.61) * _gridSize;
            return raylib::Vector3(4.47, 1.08, 17.45) * _gridSize;
        }
        if (_mapX == 30 && _mapY == 30)
            return getStartPos() + raylib::Vector3(0, -3, 7) * _gridSize;
        return getStartPos() + raylib::Vector3(0, 0, 5) * _gridSize;
    }
}
