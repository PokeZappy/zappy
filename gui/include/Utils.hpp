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
    enum class Orientation {
        NONE,
        NORTH,
        EAST,
        SOUTH,
        WEST
    };
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

        static std::string remove_extension(const std::string& filename) {
                size_t last_dot = filename.find_last_of(".");
                if (last_dot == std::string::npos) {
                    return filename;
                }
                return filename.substr(0, last_dot);
            }

    };
}
