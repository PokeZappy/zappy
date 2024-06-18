/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ADisplayModule.hpp
*/

#pragma once

#include "IGraphicalModule.hpp"

namespace Zappy
{
    class AGraphicalModule : public IGraphicalModule
    {
    public:
        AGraphicalModule() = default;

        void setMapSize(int x, int y) override
        {
            _mapX = x;
            _mapY = y;
        }

    protected:
        int _mapX = -1;
        int _mapY = -1;
        size_t _gridSize = 50;
    };
};
