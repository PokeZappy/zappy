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

    private:
        int _mapX = -1;
        int _mapY = -1;
    };
};