/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Tile.hpp
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
    class Tile {
        public:
            Tile(size_t food = 0, size_t linemate = 0, size_t deraumere = 0,
                size_t sibur = 0, size_t mendiane = 0, size_t phiras = 0,
                size_t thystame = 0, size_t players = 0, size_t eggs = 0) :
                _food(food), _linemate(linemate), _deraumere(deraumere),
                _sibur(sibur), _mendiane(mendiane), _phiras(phiras),
                _thystame(thystame), _players(players), _eggs(eggs) {}
            Tile(std::istringstream &stream) {
                stream >> _food >> _linemate >> _deraumere >> _sibur >> _mendiane
                    >> _phiras >> _thystame >> _players >> _eggs;
            }
            ~Tile() = default;
            size_t getItem(size_t index) {
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
            // size_t getFood(void) { return (_food); }
            // size_t getLinemate(void) { return (_linemate); }
            // size_t getDeraumere(void) { return (_deraumere); }
            // size_t getSibur(void) { return (_sibur); }
            // size_t getMendiane(void) { return (_mendiane); }
            // size_t getPhiras(void) { return (_phiras); }
            // size_t getThystame(void) { return (_thystame); }
            // size_t getPlayers(void) { return (_players); }
            // size_t getEggs(void) { return (_eggs); }
            // void setFood(size_t food) { _food = food; }
            // void setLinemate(size_t linemate) { _linemate = linemate; }
            // void setDeraumere(size_t deraumere) { _deraumere = deraumere; }
            // void setSibur(size_t sibur) { _sibur = sibur; }
            // void setMendiane(size_t mendiane) { _mendiane = mendiane;}
            // void setPhiras(size_t phiras) { _phiras = phiras; }
            // void setThystame(size_t thystame) { _thystame = thystame; }
            // void setPlayers(size_t players) { _players = players; }
            // void setEggs(size_t eggs) { _eggs = eggs; }
        // private:
            size_t _food = 0;
            size_t _linemate = 0;
            size_t _deraumere = 0;
            size_t _sibur = 0;
            size_t _mendiane = 0;
            size_t _phiras = 0;
            size_t _thystame = 0;
            size_t _players = 0;
            size_t _eggs = 0;
    };
}
