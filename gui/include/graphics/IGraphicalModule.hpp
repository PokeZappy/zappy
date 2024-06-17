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
        virtual void render(const Zappy::World &world) = 0;
        virtual void update() = 0;
        virtual bool isOpen() = 0;
        virtual void drawTiles(const std::vector<std::vector<Tile>> &tiles) = 0;
        virtual void drawEntity(const std::shared_ptr<IEntity> entity) = 0;
    };
};