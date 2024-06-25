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
#define GUI_WIDTH 1920
#ifdef MACBOOK
#define GUI_HEIGHT 1200
#else
#define GUI_HEIGHT 1080
#endif

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
