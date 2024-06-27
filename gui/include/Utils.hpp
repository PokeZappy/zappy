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
            static int random(int min, int max) {
                static std::random_device rd;
                static std::mt19937 gen(rd());

                std::uniform_int_distribution<> distr(min, max);

                return distr(gen);
            }
            static float generateRandomFloat(float delta) {
                float floatPrecision = 100000.;
                return Utils::random(- delta / 2. * floatPrecision, delta / 2. * floatPrecision) / floatPrecision;
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
