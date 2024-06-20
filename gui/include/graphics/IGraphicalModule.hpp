/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** IGraphicalModule.hpp
*/

#pragma once

#include "World.hpp"
#include "Tile.hpp"
#include "IEntity.hpp"

namespace Zappy
{
    class IGraphicalModule
    {
    public:
        virtual ~IGraphicalModule() = default;
        virtual void render(const World &world) = 0;
        virtual void update(const World &world) = 0;
        virtual bool isOpen(void) = 0;
        virtual void drawTiles(const std::vector<std::vector<Tile>> &tiles) = 0;
        virtual void setMapSize(int x, int y) = 0;
    };
};
