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
                _food(food), _linemate(linemate), _deraumere(deraumere),
                _sibur(sibur), _mendiane(mendiane), _phiras(phiras),
                _thystame(thystame) {}
            Inventory(std::istringstream &stream) {
                stream >> _food >> _linemate >> _deraumere >> _sibur >> _mendiane
                    >> _phiras >> _thystame;
            }
            ~Inventory() = default;
            size_t getItem(size_t index) const {
                switch ((Item)index) {
                    case Item::FOOD: return (_food);
                    case Item::LINEMATE: return (_linemate);
                    case Item::DERAUMERE: return (_deraumere);
                    case Item::SIBUR: return (_sibur);
                    case Item::MENDIANE: return (_mendiane);
                    case Item::PHIRAS: return (_phiras);
                    case Item::THYSTAME: return (_thystame);
                    default: return (0);
                }
            }
            size_t _food = 0;
            size_t _linemate = 0;
            size_t _deraumere = 0;
            size_t _sibur = 0;
            size_t _mendiane = 0;
            size_t _phiras = 0;
            size_t _thystame = 0;
    };
}
