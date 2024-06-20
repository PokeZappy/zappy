/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** IEntityRaylib.hpp
*/

#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include "raylib-cpp.hpp"

namespace Zappy
{
    class IEntityRaylib
    {
        public:
            virtual ~IEntityRaylib() = default;
            virtual void kill(void) = 0;
            virtual bool isDying(void) const = 0;
            virtual int getAnimationIndex(const std::vector<std::string> &names) = 0;
            virtual float getHeight(void) const = 0;
            virtual void setHeight(float height) = 0;
            virtual void move(raylib::Vector3 vector) = 0;
            virtual raylib::Vector3 getPosition(void) const = 0;
            virtual void draw(const raylib::Camera camera) = 0;
            virtual void update(void) = 0;
            virtual void loadTextureAndModel(void) = 0;
    };
}
