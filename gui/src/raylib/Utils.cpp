/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Utils.cpp
*/

#include "Raylib.hpp"

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
}