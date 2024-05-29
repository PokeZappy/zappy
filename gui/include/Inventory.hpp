/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Inventory.hpp
*/

#pragma once

#include <iostream>
#include <sstream>

namespace Zappy {
    enum class Item {
        FOOD,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME
    };
    class Inventory {
        public:
            Inventory(size_t food = 0, size_t linemate = 0, size_t deraumere = 0,
                size_t sibur = 0, size_t mendiane = 0, size_t phiras = 0,
                size_t thystame = 0) :
                food(food), linemate(linemate), deraumere(deraumere),
                sibur(sibur), mendiane(mendiane), phiras(phiras),
                thystame(thystame) {}
            Inventory(std::istringstream &stream) {
                stream >> food >> linemate >> deraumere >> sibur >> mendiane
                    >> phiras >> thystame;
            }
            ~Inventory() = default;
            size_t getItem(size_t index) const {
                switch ((Item)index) {
                    case Item::FOOD: return (food);
                    case Item::LINEMATE: return (linemate);
                    case Item::DERAUMERE: return (deraumere);
                    case Item::SIBUR: return (sibur);
                    case Item::MENDIANE: return (mendiane);
                    case Item::PHIRAS: return (phiras);
                    case Item::THYSTAME: return (thystame);
                    default: return (0);
                }
            }
            size_t food = 0;
            size_t linemate = 0;
            size_t deraumere = 0;
            size_t sibur = 0;
            size_t mendiane = 0;
            size_t phiras = 0;
            size_t thystame = 0;
    };
}
