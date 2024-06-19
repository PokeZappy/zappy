/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Utils.hpp
*/

#pragma once

namespace Zappy {
    class Utils {
        public:
            static float generateRandomFloat(size_t delta) {
                return (float)(rand() % delta) - delta / 2;
            }
    };
}
