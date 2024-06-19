/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Utils.hpp
*/

#pragma once

#include <random>

namespace Zappy
{
#define GRID_SIZE 20
    class Utils
    {
        public:
            static int random(int min, int max)
            {
                static std::random_device rd; 
                static std::mt19937 gen(rd());

                std::uniform_int_distribution<> distr(min, max);

                return distr(gen);
            }
            static float generateRandomFloat(size_t delta) {
                return (float)(rand() % delta) - delta / 2;
            }
    };
}
