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

        int _mapX = 10;
        int _mapY = 10;
    protected:
    };
};
