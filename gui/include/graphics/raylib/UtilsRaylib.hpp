/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Raylib.hpp
*/

#pragma once

#include "raylib-cpp.hpp"

namespace Zappy
{
    class UtilsRaylib {
    public:
        static Rectangle getTypeRectangle(std::string team) {
            int width = 32;
            if (team == "bug") {
                return raylib::Rectangle(0, 14, width, 14);
            } else if (team == "dark") {
                return raylib::Rectangle(0, 28, width, 14);
            } else if (team == "dragon") {
                return  raylib::Rectangle(0, 42, width, 14);
            } else if (team == "electric") {
                return raylib::Rectangle(0, 56, width, 14);
            } else if (team == "fairy") {
                return raylib::Rectangle(0, 70, width, 14);
            } else if (team == "fight") {
                return raylib::Rectangle(0, 84, width, 14);
            } else if (team == "fire") {
                return raylib::Rectangle(0, 98, width, 14);
            } else if (team == "fly") {
                return raylib::Rectangle(0, 112, width, 14);
            } else if (team == "ghost") {
                return raylib::Rectangle(0, 126, width, 14);
            } else if (team == "grass") {
                return raylib::Rectangle(0, 140, width, 14);
            } else if (team == "ground") {
                return raylib::Rectangle(0, 154, width, 14);
            } else if (team == "ice") {
                return raylib::Rectangle(0, 168, width, 14);
            } else if (team == "normal") {
                return raylib::Rectangle(0, 182, width, 14);
            } else if (team == "poison") {
                return raylib::Rectangle(0, 196, width, 14);
            } else if (team == "psychic") {
                return raylib::Rectangle(0, 210, width, 14);
            } else if (team == "rock") {
                return raylib::Rectangle(0, 224, width, 14);
            } else if (team == "steel") {
                return raylib::Rectangle(0, 238, width, 14);
            } else if (team == "water") {
                return raylib::Rectangle(0, 252, width, 14);
            } else {
                return raylib::Rectangle(-1, -1, -1, -1);
            }
        }
    };
}
